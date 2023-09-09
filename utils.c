/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:32:22 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 01:41:06 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_write(t_data *philo, char *status)
{
	unsigned long long	t;

	pthread_mutex_lock(philo->write);
	t = gettime() - philo->milsec;
	printf("%llu philo %d is %s \n", t, philo->whc_philo + 1, status);
	pthread_mutex_unlock(philo->write);
}

int	ft_atoi(const char *str)
{
	long	sign;
	long	result;
	long	idx;

	sign = 1;
	result = 0;
	idx = 0;
	while ((str[idx] >= 9 && str[idx] <= 13) || str[idx] == 32)
		idx++;
	if (str[idx] == '-' || str[idx] == '+')
	{
		if (str[idx] == '-')
			sign *= -1;
		idx++;
	}
	while (str[idx] && str[idx] <= '9' && str[idx] >= '0')
	{
		result = (result * 10) + (str[idx] - 48) * sign;
		if (result > 2147483647)
			return (-1);
		if (result < -2147483648)
			return (0);
		idx++;
	}
	return (result);
}
