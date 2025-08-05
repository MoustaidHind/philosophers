#include "philo.h"

void *simulation(void *ph)
{
	t_philo			*philos;
	long long		start_time;
	int				i = 0;

	philos = (t_philo *)ph;
	start_time = get_time_ms();

	if(philos->g_data->times_must_eat != 0)
	{
		while (i < philos->g_data->times_must_eat)
		{
			eating(philos, start_time);
			sleeping(philos, start_time);
			thinking(philos, start_time);
			i++;
		}
	}
	else // true while loop
	{ 
		while (1)
		{	

			eating(philos, start_time);
			sleeping(philos, start_time);
			thinking(philos, start_time);
		}
	}
	return(NULL);
}

void thinking(t_philo *philo, long long start_time)
{
	long long ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is thinking");
}

void sleeping(t_philo *philo, long long start_time)
{
	long long ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is sleeping");
	ft_usleep(philo->g_data->time_to_sleep);
}


/* 
ti = 153 (how much time passed when we start simulation)
last_meal = 0 or (100 for second pair)

timetodie = 150
*/


void eating(t_philo *philo, long long start_time)
{
	int			f1;
	int			f2;
	long long	ti;

	f1 = philo->left_fork;
	f2 = philo->right_fork;

	
	pthread_mutex_lock(&philo->forks[f1]);
	pthread_mutex_lock(&philo->forks[f2]);
	
	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "has taken a fork");
	ft_print(philo, ti, "has taken a fork");
	ft_print(philo, ti, "is eating");

	philo->last_time_eat = get_time_ms() - start_time;

	ft_usleep(philo->g_data->time_to_eat);

	pthread_mutex_unlock(&philo->forks[f1]);
	pthread_mutex_unlock(&philo->forks[f2]);
}

