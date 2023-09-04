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
	int left_fork;
	int right_fork;
	int *adress_lf;
	int *adress_rf;


} t_data;

#endif
