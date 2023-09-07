/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:17:17 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/07 14:23:14 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void init(char **ag,t_data **philo,pthread_mutex_t **mutx, pthread_mutex_t *write,pthread_mutex_t *death)
{
	int num = atoi(ag[1]);
	int i = 0;
	pthread_mutex_t *mutex = (*mutx);
	while (i<num)
	{
		if (i == 0)
			(*philo)[0].rf = &(*mutx)[num-1];
		else
			(*philo)[i].rf = &(*mutx)[i-1];
		(*philo)[i].lf= &(*mutx)[i];
		(*philo)[i].philo_num = atoi(ag[1]);
		(*philo)[i].time_die = atoi(ag[2]);
		(*philo)[i].time_eat = atoi(ag[3]);
		(*philo)[i].time_sleep = atoi(ag[4]);
		(*philo)[i].write = write;
		(*philo)[i].death = death;
		(*philo)[i].milsec = gettime();
		(*philo)[i].last_eat = gettime();
		i++;
	}
}

void mutex_start(char **ag,pthread_mutex_t **mutx, pthread_mutex_t *write,pthread_mutex_t *death)
{
	int num = atoi(ag[1]);
	int i = 0;
	while (i<num)
	{
		pthread_mutex_init(&(*mutx)[i],NULL);
		i++;
	}
	pthread_mutex_init(write,NULL);
	pthread_mutex_init(death,NULL);
}

void thread_start(char **ag, pthread_t **thread_id, t_data **philo)
{
	int i = 0;
	int num = atoi(ag[1]);
		while (i < num)
	{
		(*philo)[i].whc_philo = i;
		pthread_create(&(*thread_id)[i], NULL, ft_sender, &(*philo)[i]);
		i+=2;

	}
	usleep(200);
	i = 1;
	while (i < num)
	{
		(*philo)[i].whc_philo = i;
		pthread_create(&(*thread_id)[i], NULL, ft_sender, &(*philo)[i]);
		i+=2;
	}
}
