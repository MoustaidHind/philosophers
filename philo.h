#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct data
{
	long	nbr_of_philo;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	long	times_must_eat;
} t_data;

typedef struct philo
{
	int 		num_philo;
	int 		left_fork; // index in the mutex array
	int 		right_fork;
	
	long long 	last_time_eat; // last time eat to check 
	
	int			dead;

	t_data		*g_data;
	pthread_mutex_t write_mutex;
	pthread_mutex_t	*forks;

} t_philo;

long	ft_atoi(const char *str);
char	*ft_strjoin(char const *s1, char const *s2);

size_t	ft_strlen(const char *str);


int is_number(char *str);
int valide_args(char **av);
int args_to_nbrs(t_data *data, int ac, char **av);
int error_msg();
int clean_data(t_data *data);

pthread_mutex_t	*forks(t_data *data);
t_philo			*philo_infos(t_data *data, pthread_mutex_t *arr_forks);
pthread_t		*create_philo(t_data *data, t_philo *philos);

void *simulation(void *ph);

void eating(t_philo *philo, long long start_time);
void sleeping(t_philo *philo, long long start_time);
void thinking(t_philo *philo, long long start_time);
void is_dead(t_philo *philo, long long start_time);

void ft_usleep(int timing_ms);
void ft_print(t_philo *philo, long long timestamp, char *str);
long long get_time_ms();


#endif