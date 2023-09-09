/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:32:29 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 00:49:38 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_control(t_data **philo, char **ag, pthread_t **thread_id)
{
	int	i;

	while (1)
	{
		i = 0;
		while (i < (*philo)[0].philo_num)
		{
			pthread_mutex_lock((*philo)[i].death);
			pthread_mutex_lock((*philo)[i].write);
			if ((gettime() - (*philo)[i].last_eat) >
				(*philo)[i].time_die || eat_control((*philo)))
			{
				if ((gettime() - (*philo)[i].last_eat) > (*philo)[i].time_die)
					printf("%llu  %d is dead\n", gettime() - (*philo)[i].milsec,
						(*philo)[i].whc_philo);
				pthread_mutex_unlock((*philo)->death);
				ft_detach(ag, &thread_id);
				return ;
			}
			else
				pthread_mutex_unlock((*philo)[i].write);
			pthread_mutex_unlock((*philo)->death);
			i++;
		}
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
