/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:32:29 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 11:18:49 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_control(t_data **philo)
{
	int	i;

	while (1)
	{
		pthread_mutex_lock((*philo)[0].death);
		pthread_mutex_lock((*philo)[0].write);
		if ((*philo)[0].num_eat_max != -1)
		{
			if (eat_control((*philo)))
			{
				(*philo)[0].death_status = 7;
				return ;
			}
		}
		i = dead_control((*philo));
		if (i != -1)
		{
			(*philo)[0].death_status = 7;
			printf("%llu philo %d is dead\n", gettime()
				- (*philo)[i].milsec, (*philo)[i].whc_philo + 1);
			return ;
		}
		pthread_mutex_unlock((*philo)[0].write);
		pthread_mutex_unlock((*philo)[0].death);
	}
}

int	eat_control(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].philo_num)
	{
		if (philo[i].num_eat < philo[i].num_eat_max)
			return (0);
		i++;
	}
	return (1);
}

int	dead_control(t_data *philo)
{
	int	i;

	i = 0;
	while (i < philo[0].philo_num)
	{
		if ((int)(gettime() - philo[i].last_eat) >= philo[i].time_die)
			return (i);
		i++;
	}
	return (-1);
}
