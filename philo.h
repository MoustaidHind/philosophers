/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:27 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:29 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct data
{
	long			nbr_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			times_must_eat;
	int				many_times_eat;
	int				dead;
	pthread_mutex_t	g_mutex;
	pthread_mutex_t	many_times_eat_mutexx;
	pthread_mutex_t	dead_mutexx;
}	t_data;

typedef struct philo
{
	int				num_philo;
	int				left_fork;
	int				right_fork;
	long long		start_time;
	long long		last_time_eat;
	t_data			*g_data;
	pthread_mutex_t	write_mutex;
	pthread_mutex_t	*forks;
}	t_philo;

long			ft_atoi(const char *str);

int				is_number(char *str);
int				valide_args(char **av);
int				args_to_nbrs(t_data *data, int ac, char **av);
int				error_msg(char *str);
int				clean_data(t_data *data, char *str);

pthread_mutex_t	*forks(t_data *data);
t_philo			*philo_infos(t_data *data, pthread_mutex_t *arr_forks);
pthread_t		*create_philo(t_data *dt, t_philo *ph, pthread_mutex_t *forks);
int				create_odd_even_philos(t_data *dt, t_philo *ph, pthread_t *th);

void			*simulation(void *ph);
void			lock_forks(t_philo *philo);
void			eating(t_philo *philo, long long start_time);
void			sleeping(t_philo *philo, long long start_time);
void			thinking(t_philo *philo, long long start_time);

char			*is_dead(t_data *data, t_philo *philo);
char			*philo_dead(t_data *dt, t_philo *ph, long long time, int i);
int				check_meals_and_dead(t_data *d, t_philo *p, long long t, int i);
int				check_dead(t_data *data, t_philo *philo, long long ti, int i);

void			ft_usleep(int timing_ms);
void			ft_print(t_philo *philo, long long timestamp, char *str);
long long		get_time_ms(void);

void			clean_up(t_philo *ph, pthread_mutex_t *forks, pthread_t *th);

#endif