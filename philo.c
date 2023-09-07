/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/07 14:09:17 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"


void	ft_sleep(t_data *dnm)
{
	unsigned long long t;
	t = gettime();

		pthread_mutex_lock(dnm->write);

		printf("%llu  %d is sleeping \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);

		pthread_mutex_unlock(dnm->lf);
		pthread_mutex_unlock(dnm->rf);

		ft_wait(dnm->time_sleep-gettime()+t);
}
void eat(t_data *dnm)
{

	unsigned long long t;
	pthread_mutex_lock(dnm->lf);
	pthread_mutex_lock(dnm->write);
	printf("%llu  %d is take a leftfork \n", gettime()-dnm->milsec,dnm->whc_philo);
	pthread_mutex_unlock(dnm->write);
	pthread_mutex_lock(dnm->rf);
	t = gettime();
		pthread_mutex_lock(dnm->write);
		printf("%llu  %d is take a right fork \n",gettime()-dnm->milsec,dnm->whc_philo);
		printf("%llu  %d is eating \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);
		dnm->last_eat = gettime();
		ft_wait(dnm->time_eat-gettime()+t);
}

void	*ft_sender(void *philo)
{
	t_data *dnm = philo;
	while(1)
	{
		eat(dnm);
		ft_sleep(dnm);
		pthread_mutex_lock(dnm->write);
		printf("%llu  %d is thinking \n", gettime()-dnm->milsec,dnm->whc_philo);
		pthread_mutex_unlock(dnm->write);
	}
	return(0);
}

int	main(int ac, char **ag)
{
	pthread_t *thread_id;
	t_data *philo;
	int i = 0;
	pthread_mutex_t *mutx;
	pthread_mutex_t write;
	pthread_mutex_t death;
	int num = atoi(ag[1]);

	philo = malloc( atoi(ag[1])*sizeof(t_data));
	thread_id = malloc( atoi(ag[1])*sizeof(pthread_t));
	mutx = malloc( atoi(ag[1])*sizeof(pthread_mutex_t));

	mutex_start(ag,&mutx, &write, &death);
	init(ag,&philo,&mutx, &write, &death);

	thread_start(ag, &thread_id, &philo);
	ft_control(&philo);
	while (i < num)
	{
		pthread_detach(thread_id[i]);
		i++;
	}


}
