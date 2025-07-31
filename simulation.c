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
			// is_dead(philos, start_time);

			i++;
		}
	}
	else // true while loop
	{
		eating(philos, start_time);
		sleeping(philos, start_time);
		thinking(philos, start_time);
	}

	return(NULL);
}

void thinking(t_philo *philo, long long start_time)
{
	long long ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is thinking");
	is_dead(philo, start_time);

}

void sleeping(t_philo *philo, long long start_time)
{
	long long ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is sleeping");
	ft_usleep(philo->g_data->time_to_sleep);
	is_dead(philo, start_time);

}

void is_dead(t_philo *philo, long long start_time)
{
	long long ti;

	ti = get_time_ms() - start_time;

	if(philo->last_time_eat >= philo->g_data->time_to_die)
	{
		philo->dead = 1;
		ft_print(philo, ti, "---------------------------> died XXXX");
	}
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

	philo->last_time_eat = (get_time_ms() - start_time) - philo->last_time_eat;
	
	//printf("--> (%d) i start eat since  (%lld)ms\n",philo->num_philo, philo->last_time_eat);
	
	ft_usleep(philo->g_data->time_to_eat);

	is_dead(philo, start_time);

	pthread_mutex_unlock(&philo->forks[f1]);
	pthread_mutex_unlock(&philo->forks[f2]);

}
