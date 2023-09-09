/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:32:22 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/09 22:50:19 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_write(t_data *philo, char *status)
{
	unsigned long long	t;

	pthread_mutex_lock(philo->write);
	t = gettime() - philo->milsec;
	printf("%llu %d philo is %s \n", t, philo->whc_philo + 1, status);
	pthread_mutex_unlock(philo->write);
}
