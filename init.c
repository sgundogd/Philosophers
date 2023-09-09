/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 12:17:17 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 02:08:53 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	init(char **ag, t_data **philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(ag[1]))
	{
		(*philo)[i].philo_num = ft_atoi(ag[1]);
		(*philo)[i].time_die = ft_atoi(ag[2]);
		(*philo)[i].time_eat = ft_atoi(ag[3]);
		(*philo)[i].time_sleep = ft_atoi(ag[4]);
		if (ag[5])
			(*philo)[i].num_eat_max = ft_atoi(ag[5]);
		else
			(*philo)[i].num_eat_max = -1;
		(*philo)[i].num_eat = 0;
		(*philo)[i].milsec = gettime();
		(*philo)[i].last_eat = gettime();
		i++;
	}
}

void	mutex_start(t_data **philo, pthread_mutex_t **mutx,
	pthread_mutex_t *write, pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < (*philo)[0].philo_num)
	{
		pthread_mutex_init(&(*mutx)[i], NULL);
		i++;
	}
	pthread_mutex_init(write, NULL);
	pthread_mutex_init(death, NULL);
	i = 0;
	while (i < (*philo)[0].philo_num)
	{
		if (i == 0)
			(*philo)[0].rf = &(*mutx)[(*philo)[0].philo_num - 1];
		else
			(*philo)[i].rf = &(*mutx)[i - 1];
		(*philo)[i].lf = &(*mutx)[i];
		(*philo)[i].write = write;
		(*philo)[i].death = death;
		i++;
	}
}

void	thread_start(char **ag, pthread_t **thread_id, t_data **philo)
{
	int	i;

	i = 0;
	while (i < ft_atoi(ag[1]))
	{
		(*philo)[i].whc_philo = i;
		pthread_create(&(*thread_id)[i], NULL, ft_sender, &(*philo)[i]);
		i += 2;
	}
	usleep(200);
	i = 1;
	while (i < ft_atoi(ag[1]))
	{
		(*philo)[i].whc_philo = i;
		pthread_create(&(*thread_id)[i], NULL, ft_sender, &(*philo)[i]);
		i += 2;
	}
}

void	ft_detach(char **ag, pthread_t **thread_id)
{
	int	i;

	i = 0;
	while (i < ft_atoi(ag[1]))
	{
		pthread_detach((*thread_id)[i]);
		i++;
	}
}
