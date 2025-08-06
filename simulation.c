/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:35 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:36 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "philo.h"

int main_routine(t_philo	*philos, long long	start_time)
{
	pthread_mutex_lock(&(philos->g_data->dead_mutexx));
	if(philos->g_data->dead == 1)
	{
		pthread_mutex_unlock(&(philos->g_data->dead_mutexx));
		return(-1);
	}
	pthread_mutex_unlock(&(philos->g_data->dead_mutexx)); // unlock it even condotion not true 
	eating(philos, start_time);
	sleeping(philos, start_time);
	thinking(philos, start_time);

	return(0);
}

void *simulation(void *ph)
{
	long long		start_time;
	t_philo			*philos;
	int				i;
	
	i = 0;
	philos = (t_philo *)ph;
	start_time = get_time_ms();
	if(philos->g_data->times_must_eat != 0)
	{
		while (i < philos->g_data->times_must_eat)
		{
			if(main_routine(philos, start_time) == -1)
				break;
			i++;
		}
	}
	else // true while loop
	{
		while (1)
			if(main_routine(philos, start_time) == -1)
				break;
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

