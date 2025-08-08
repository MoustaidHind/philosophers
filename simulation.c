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

int	main_routine(t_philo *philos, long long start_time)
{
	pthread_mutex_lock(&(philos->g_data->dead_mutexx));
	if (philos->g_data->dead == 1)
	{
		pthread_mutex_unlock(&(philos->g_data->dead_mutexx));
		return (-1);
	}
	pthread_mutex_unlock(&(philos->g_data->dead_mutexx));
	eating(philos, start_time);
	if (philos->g_data->nbr_of_philo == 1)
		return (-1);
	sleeping(philos, start_time);
	thinking(philos, start_time);
	return (0);
}

void	*simulation(void *ph)
{
	t_philo			*philos;
	int				i;

	i = 0;
	philos = (t_philo *)ph;
	if (philos->g_data->times_must_eat != 0)
	{
		while (i < philos->g_data->times_must_eat)
		{
			if (main_routine(philos, philos->start_time) == -1)
				break ;
			i++;
		}
	}
	else
	{
		while (1)
			if (main_routine(philos, philos->start_time) == -1)
				break ;
	}
	return (NULL);
}

void	thinking(t_philo *philo, long long start_time)
{
	long long	ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is thinking");
}

void	sleeping(t_philo *philo, long long start_time)
{
	long long	ti;

	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "is sleeping");
	ft_usleep(philo->g_data->time_to_sleep);
}

void	eating(t_philo *philo, long long start_time)
{
	long long	ti;

	if (philo->g_data->nbr_of_philo == 1)
	{
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		ft_print(philo, (get_time_ms() - start_time), "has taken a fork");
		return ;
	}
	if(philo->num_philo % 2 == 0)
	{
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
	}
	else
	{
		pthread_mutex_lock(&philo->forks[philo->left_fork]);
		pthread_mutex_lock(&philo->forks[philo->right_fork]);
	}
	ti = get_time_ms() - start_time;
	ft_print(philo, ti, "has taken a fork");
	ft_print(philo, ti, "has taken a fork");
	ft_print(philo, ti, "is eating");
	pthread_mutex_lock(&(philo->g_data->g_mutex));
	philo->last_time_eat = get_time_ms() - start_time;
	pthread_mutex_unlock(&(philo->g_data->g_mutex));
	pthread_mutex_lock(&(philo->g_data->many_times_eat_mutexx));
	philo->g_data->many_times_eat++;
	pthread_mutex_unlock(&(philo->g_data->many_times_eat_mutexx));
	ft_usleep(philo->g_data->time_to_eat);
	pthread_mutex_unlock(&philo->forks[philo->left_fork]);
	pthread_mutex_unlock(&philo->forks[philo->right_fork]);
}
