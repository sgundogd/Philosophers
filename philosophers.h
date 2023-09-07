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
	int ms;
	int ms_hungry;
	int think_status;
	int eat_status;
	int sleep_status;
	pthread_mutex_t *rf;
	pthread_mutex_t *lf;
	pthread_mutex_t *write;
	unsigned long long milsec;



} t_data;

unsigned long long gettime(void);
void	*ft_sender(void *philo);
int eat(t_data *dnm);
int ft_sleep(t_data *dnm);
void ft_wait(int second);

#endif
