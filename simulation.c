#include "philo.h"

void *simulation(void *ph)
{
	t_philo			*philos;
	long long		current_time;
	int				i = 0;

	current_time = get_time_ms();
	// printf("current time %lld\n", current_time);
	philos = (t_philo *)ph;
	if(philos->g_data->times_must_eat != 0)
	{
		while (i < philos->g_data->times_must_eat)
		{
			eating(philos, current_time);
			sleeping(philos, current_time);
			thinking(philos, current_time);
			i++;
		}
	}
	else
	{
		eating(philos, current_time);
		sleeping(philos, current_time);
		thinking(philos, current_time);
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

void eating(t_philo *philo, long long start_time)
{
	int f1;
	int f2;

	long long ti;


	f1 = philo->left_fork;
	f2 = philo->right_fork;

	pthread_mutex_lock(&philo->forks[f1]);
	pthread_mutex_lock(&philo->forks[f2]);

	ti = get_time_ms() - start_time;

	ft_print(philo, ti, "has taken a fork");
	ft_print(philo, ti, "is eating");

	ft_usleep(philo->g_data->time_to_eat);

	pthread_mutex_unlock(&philo->forks[f1]);
	pthread_mutex_unlock(&philo->forks[f2]);

}