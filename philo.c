/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/04 17:08:10 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

pthread_mutex_t lock;

void ft_sleep(t_data *dnm)
{
	if(dnm->sleep_status == 1)
	{
		printf("%d  %d is sleeping \n", dnm->ms,dnm->whc_philo);
		pthread_mutex_lock(&lock);

		dnm->ms += dnm->time_sleep;
		*(dnm->adress_lf) = 0;
		*(dnm->adress_rf) = 0;
		pthread_mutex_unlock(&lock);
		usleep(40);

	}


}
void eat(t_data *dnm)
{
	pthread_mutex_lock(&lock);
	if(dnm->right_fork == 0 && dnm->left_fork == 0)
	{
		dnm->right_fork = -1;
		dnm->left_fork = -1;
		*(dnm->adress_lf) = -1;
		*(dnm->adress_rf) = -1;
		dnm->sleep_status = 1;
		printf("%d  %d is eating \n", dnm->ms,dnm->whc_philo);
	}
	else
	{
		dnm->sleep_status = 0;
		//printf("%d  %d is not eating %d  %d\n", dnm->ms,dnm->whc_philo,dnm->right_fork, dnm->left_fork);

	}
	dnm->ms += dnm->time_eat;
	pthread_mutex_unlock(&lock);

	//ft_sleep(dnm);

}

int ft_dead(t_data *dnm)
{
	if(dnm->ms > dnm->time_die)
		return(-1);
	else
		return(0);

}

void sender(t_data *dnm)
{

	//int a = ft_dead(dnm);
	int i = 0;
	while(i++ <= 5)
	{

		eat(dnm);
		usleep(20);
		ft_sleep(dnm);
		usleep(20);
	}
		//ft_sleep(dnm);
		//a = ft_dead(dnm);
	/*pthread_mutex_lock(&lock);
	printf("öldü  %d\n",dnm->whc_philo);
	exit(0);
	pthread_mutex_unlock(&lock);*/


	//pthread_mutex_lock(&lock);

	//usleep(1000);
	//printf("merhaba  %d\n",dnm->whc_philo);
	//pthread_mutex_unlock(&lock);
	//dnm->ms += 200;


}

void	*ft_dene(void *dnm)
{
	sender(dnm);
	return(0);

}

int	main(int ac, char **ag)
{
	int			i;
	pthread_t *thread_id;
	t_data *philo;

	pthread_mutex_init(&lock, NULL);


	philo = malloc(5*sizeof(t_data));
	thread_id = malloc(5*sizeof(pthread_t));
	int num = atoi(ag[1]);
	i = 0;

	while (i<num)
	{
		if (i == 0)
		{
			philo[0].adress_lf = &philo[1].right_fork;
			philo[0].adress_rf = &philo[num-1].left_fork;
		}
		else if(i == num-1)
		{
		philo[num-1].adress_lf = &philo[0].right_fork;
		philo[num-1].adress_rf = &philo[num-2].left_fork;

		}
		else
		{

		philo[i].adress_lf = &philo[i+1].right_fork;
		philo[i].adress_rf = &philo[i-1].left_fork;
		}

		philo[i].philo_num = atoi(ag[1]);
		philo[i].time_die = atoi(ag[2]);
		philo[i].time_eat = atoi(ag[3]);
		philo[i].time_sleep = atoi(ag[4]);
		i++;
	}

	i = 0;
	while (i < num)
	{
		philo[i].whc_philo = i;
		pthread_create(&thread_id[i], NULL, ft_dene, &philo[i]);
		i++;
	}
	i = 0;
	while (i < num) {
        pthread_join(thread_id[i], NULL);
        i++;
    }

	return (0);
}
