#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

typedef struct s_data
{
	int philo_num;
	int time_die;
	int time_eat;
	int time_sleep;
	int num_eat;
	int whc_philo;
	pthread_mutex_t *rf;
	pthread_mutex_t *lf;
	pthread_mutex_t *write;
	pthread_mutex_t *death;
	unsigned long long milsec;
	unsigned long long last_eat;
} t_data;

unsigned long long gettime(void);
void	*ft_sender(void *philo);
void eat(t_data *dnm);
void	ft_sleep(t_data *dnm);
void ft_wait(int second);
void init(char **ag,t_data **dnm,pthread_mutex_t **mutx, pthread_mutex_t *write,pthread_mutex_t *death);
void mutex_start(char **ag,pthread_mutex_t **mutx, pthread_mutex_t *write,pthread_mutex_t *death);
void thread_start(char **ag, pthread_t **thread_id, t_data **philo);
void ft_control(t_data **philo);

#endif
