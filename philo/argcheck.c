/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   argcheck.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/10 13:48:00 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 14:06:09 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_argument(int ac, char **ag)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_isdigit(ag[i]) == -1 || ft_isall(ag[i]) == -1
			|| ft_atoi(ag[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	ft_isdigit(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if (a[i] >= '0' && a[i] <= '9')
			return (1);
		i++;
	}
	return (-1);
}

int	ft_isall(char *a)
{
	int	i;

	i = 0;
	while (a[i])
	{
		if ((a[i] >= '0' && a[i] <= '9') || a[i] == '+' || a[i] == ' ')
			i++;
		else
			return (-1);
	}
	return (1);
}
