/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/06 23:26:51 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/07 11:41:51 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long long gettime(void)
{
	struct timeval tv;
	unsigned long long t;
	gettimeofday(&tv,NULL);

	t = tv.tv_usec/1000 + tv.tv_sec*1000;
	return (t);

}

void ft_wait(int second)
{

	unsigned long long t;

	t = gettime();
	while (gettime()-t < second)
	{
		usleep(100);
	}

}

