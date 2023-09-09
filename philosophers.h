/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sgundogd <sgundogd@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/09 22:25:41 by sgundogd          #+#    #+#             */
/*   Updated: 2023/09/10 02:09:42 by sgundogd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct s_data
{
	int					philo_num;
	int					time_die;
	int					time_eat;
	int					time_sleep;
	int					num_eat;
	int					num_eat_max;
	int					whc_philo;
	pthread_mutex_t		*rf;
	pthread_mutex_t		*lf;
	pthread_mutex_t		*write;
	pthread_mutex_t		*death;
	unsigned long long	milsec;
	unsigned long long	last_eat;
}	t_data;

unsigned long long	gettime(void);
void				*ft_sender(void *philo);
void				eat(t_data *dnm);
void				ft_sleep(t_data *dnm);
void				ft_wait(int second);
void				init(char **ag, t_data **philo);
void				mutex_start(t_data **philo, pthread_mutex_t **mutx,
						pthread_mutex_t *write, pthread_mutex_t *death);
void				thread_start(char **ag, pthread_t **thread_id,
						t_data **philo);
void				ft_control(t_data **philo, char **ag,
						pthread_t **thread_id);
int					eat_control(t_data *philo);
void				ft_detach(char **ag, pthread_t **thread_id);
void				ft_write(t_data *philo, char *status);
int					dead_control(t_data *philo);
int					ft_atoi(const char *str);

#endif
