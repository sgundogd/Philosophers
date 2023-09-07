/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/07 02:08:47 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


int ft_sleep(t_data *dnm)
{
	unsigned long long t;
	t = gettime();

	if(dnm->ms_hungry >dnm->time_die)
		return(0);
	else
	{
		pthread_mutex_lock(dnm->write);

		printf("%llu  %d is sleeping \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);
		if(dnm->ms_hungry >dnm->time_die)
			return(0);

		pthread_mutex_unlock(dnm->lf);
		pthread_mutex_unlock(dnm->rf);

		ft_wait(dnm->time_sleep-gettime()+t);
	}
	return(1);
}
int eat(t_data *dnm)
{

	unsigned long long t;
	pthread_mutex_lock(dnm->lf);
	pthread_mutex_lock(dnm->write);
	printf("%llu  %d is take a leftfork \n", gettime()-dnm->milsec,dnm->whc_philo);
	pthread_mutex_unlock(dnm->write);
	pthread_mutex_lock(dnm->rf);
	t = gettime();
		if(dnm->ms_hungry >dnm->time_die)
			return(0);
			pthread_mutex_lock(dnm->write);
		printf("%llu  %d is take a right fork \n",gettime()-dnm->milsec,dnm->whc_philo);
		printf("%llu  %d is eating \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);

		ft_wait(dnm->time_eat-gettime()+t);


	return(1);
}

void	*ft_sender(void *philo)
{
	t_data *dnm = philo;
	while(1)
	{
		if(eat(dnm) == 0)
		{
			printf("%d  %d is dead \n", dnm->ms,dnm->whc_philo);
			exit(0);
		}
		usleep(20);
		if(ft_sleep(dnm)==0)
		{
			printf("%d  %d is dead \n", dnm->ms,dnm->whc_philo);
			exit(0);
		}
		pthread_mutex_lock(dnm->write);
		printf("%llu  %d is thinking \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);

	}
	return(0);

}
void init(char **ag,t_data **dnm,pthread_mutex_t **mutx, pthread_mutex_t *write)
{
	int num = atoi(ag[1]);
	int i = 0;
	t_data *philo = (*dnm);
	pthread_mutex_t *mutex = (*mutx);
	while (i<num)
	{
		if (i == 0)
		{
			philo[0].rf = &mutex[num-1];
		}
		else
		{
		philo[i].rf = &mutex[i-1];
		}
		philo[i].lf= &mutex[i];
		philo[i].philo_num = atoi(ag[1]);
		philo[i].time_die = atoi(ag[2]);
		philo[i].time_eat = atoi(ag[3]);
		philo[i].time_sleep = atoi(ag[4]);
		philo[i].write = write;
		philo[i].milsec = gettime();
		i++;
	}

}

int	main(int ac, char **ag)
{
	int			i;
	pthread_t *thread_id;
	t_data *philo;
	pthread_mutex_t *mutx;
	pthread_mutex_t write;
	int num = atoi(ag[1]);

	philo = malloc(num*sizeof(t_data));
	thread_id = malloc(num*sizeof(pthread_t));
	mutx = malloc(num*sizeof(pthread_mutex_t));
	i = 0;

	init(ag,&philo,&mutx, &write);
	while (i<num)
	{
		pthread_mutex_init(&mutx[i],NULL);
		i++;
	}


	i = 0;
	while (i < num)
	{
		philo[i].whc_philo = i;
		pthread_create(&thread_id[i], NULL, ft_sender, &philo[i]);
		i++;
		usleep(20);
	}
	i = 0;
	while (i < num) {
        pthread_join(thread_id[i], NULL);
        i++;
    }
}
