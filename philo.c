/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/06 20:20:27 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ms = 0;

int ft_sleep(t_data *dnm)
{

	if(dnm->ms_hungry >dnm->time_die)
		return(0);
	else
	{

		printf("%d  %d is sleeping \n", ms,dnm->whc_philo);
		ms = ms+dnm->time_sleep;
		dnm->ms += dnm->time_sleep;
		dnm->ms_hungry +=dnm->time_sleep;
		if(dnm->ms_hungry >dnm->time_die)
		return(0);
		dnm->sleep_status = 0;
		pthread_mutex_unlock(dnm->lf);
		pthread_mutex_unlock(dnm->rf);
		usleep(200);
	}

	return(1);
}
int eat(t_data *dnm)
{
	pthread_mutex_lock(dnm->lf);
	printf("%d  %d is take a fork \n", ms,dnm->whc_philo);
	pthread_mutex_lock(dnm->rf);
		if(dnm->ms_hungry >dnm->time_die)
			return(0);
		printf("%d  %d is take a right fork \n", ms,dnm->whc_philo);
		printf("%d  %d is eating \n", ms,dnm->whc_philo);
		ms = ms+dnm->time_eat;
		dnm->ms_hungry = 0;
	dnm->ms += dnm->time_eat;
	return(1);
}

void	*ft_sender(void *philo)
{
			//a = ft_dead(dnm);
	/*pthread_mutex_lock(&lock);
	printf("öldü  %d\n",dnm->whc_philo);
	exit(0);
	pthread_mutex_unlock(&lock);*/
	t_data *dnm = philo;
	int i = 0;
	while(i++ <= 5)
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
		printf("%d  %d is thinking \n", ms,dnm->whc_philo);
	}
	printf("%d\n",i);
	return(0);

}
void init(char **ag,t_data **dnm,pthread_mutex_t **mutx)
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
		i++;
	}

}

int	main(int ac, char **ag)
{
	int			i;
	pthread_t *thread_id;
	t_data *philo;
	pthread_mutex_t *mutx;
	int num = atoi(ag[1]);

	philo = malloc(num*sizeof(t_data));
	thread_id = malloc(num*sizeof(pthread_t));
	mutx = malloc(num*sizeof(pthread_mutex_t));
	i = 0;

	init(ag,&philo,&mutx);
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
