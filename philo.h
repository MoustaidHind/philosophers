#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>

typedef struct data
{
	long	nbr_of_philo;
	long	time_to_die;
	long time_to_eat;
	long time_to_sleep;
	long times_must_eat;
} t_data;


long	ft_atoi(const char *str);

int is_number(char *str);
int valide_args(char **av);
int args_to_nbrs(t_data *data, int ac, char **av);
int error_msg();
int clean_data(t_data *data);

#endif