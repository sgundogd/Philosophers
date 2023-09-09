/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 15:28:02 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 00:51:29 by sgundogd         ###   ########.fr       */
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
	philo->num_eat += 1;
	philo->last_eat = gettime();
	ft_wait(philo->time_eat - gettime() + t);
}

void	*ft_sender(void *data)
{
	t_data	*philo;

	philo = data;
	while (1)
	{
		eat(philo);
		ft_sleep(philo);
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
		philo = malloc(atoi(ag[1]) * sizeof(t_data));
		thread_id = malloc(atoi(ag[1]) * sizeof(pthread_t));
		mutx = malloc(atoi(ag[1]) * sizeof(pthread_mutex_t));
		mutex_start(ag, &mutx, &write, &death);
		init(ag, &philo, &mutx, &write, &death);
		thread_start(ag, &thread_id, &philo);
		ft_control(&philo, ag, &thread_id);
	}
}
