/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:32:29 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/07 14:09:28 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void ft_control(t_data **philo)
{
	t_data *dnm = (*philo);
	int i = 0;

	while (1)
	{
		i = 0;
		while (i < dnm[0].philo_num)
		{
			pthread_mutex_lock(dnm[i].death);
			pthread_mutex_lock(dnm[i].write);
			if(gettime()-dnm[i].last_eat > dnm[i].time_die)
			{
				printf("%llu  %d is dead\n", gettime()-dnm[i].milsec,dnm[i].whc_philo);
				pthread_mutex_unlock(dnm->death);
				return ;
			}
			else
				pthread_mutex_unlock(dnm[i].write);
			pthread_mutex_unlock(dnm->death);
			i++;

		}
	}


}
