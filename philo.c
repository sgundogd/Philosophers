/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 11:18:34 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_sleep(t_data *philo)
{
	unsigned long long	t;

	t = gettime();
	ft_write(philo, "sleeping");
	pthread_mutex_unlock(philo->lf);
	pthread_mutex_unlock(philo->rf);
	ft_wait(philo->time_sleep - gettime() + t);
}

void	eat(t_data *philo)
{
	unsigned long long	t;

	pthread_mutex_lock(philo->lf);
	ft_write(philo, "take a left fork");
	pthread_mutex_lock(philo->rf);
	t = gettime();
	ft_write(philo, "take a right fork");
	ft_write(philo, "eating");
	pthread_mutex_lock(philo->death);
	philo->num_eat += 1;
	philo->last_eat = gettime();
	pthread_mutex_unlock(philo->death);
	ft_wait(philo->time_eat - gettime() + t);
}

void	*ft_sender(void *data)
{
	t_data	*philo;

	philo = data;
	while (1)
	{
		if (*(philo->death_status_ad) != 7)
			eat(philo);
		if (*(philo->death_status_ad) != 7)
			ft_sleep(philo);
		if (*(philo->death_status_ad) != 7)
			ft_write(philo, "thinking");
	}
	return (0);
}

int	main(int ac, char **ag)
{
	pthread_mutex_t	*mutx;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_t		*thread_id;
	t_data			*philo;

	if (ac == 5 || ac == 6)
	{
		philo = malloc(ft_atoi(ag[1]) * sizeof(t_data));
		thread_id = malloc(ft_atoi(ag[1]) * sizeof(pthread_t));
		mutx = malloc(ft_atoi(ag[1]) * sizeof(pthread_mutex_t));
		if (init(ag, &philo) == -1)
			return (0);
		mutex_start(&philo, &mutx, &write, &death);
		thread_start(ag, &thread_id, &philo);
		ft_control(&philo);
		ft_detach(ag, &thread_id);
		free(mutx);
		free(thread_id);
		free(philo);
	}
	else
		return (1);
}
