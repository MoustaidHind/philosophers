/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:58:46 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:48 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

char	*philo_dead(t_data *data, t_philo *philo, long long time, int i)
{
	pthread_mutex_lock(&(data->dead_mutexx));
	data->dead = 1;
	pthread_mutex_unlock(&(data->dead_mutexx));
	printf("%lld %d %s\n", time, philo[i].num_philo, "dead");
	return (NULL);
}

int	check_meals_and_dead(t_data *data, t_philo *philo, long long ti, int i)
{
	pthread_mutex_lock(&(philo->g_data->g_mutex));
	if ((ti - philo[i].last_time_eat) > data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->g_data->g_mutex));
		pthread_mutex_lock(&(philo->g_data->many_times_eat_mutexx));
		if (data->many_times_eat == (data->nbr_of_philo * data->times_must_eat))
		{
			pthread_mutex_unlock(&(philo->g_data->many_times_eat_mutexx));
			return (1);
		}
		pthread_mutex_unlock(&(philo->g_data->many_times_eat_mutexx));
		return (2);
	}
	pthread_mutex_unlock(&(philo->g_data->g_mutex));
	return (0);
}

int	check_dead(t_data *data, t_philo *philo, long long ti, int i)
{
	pthread_mutex_lock(&(philo->g_data->g_mutex));
	if ((ti - philo[i].last_time_eat) > data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->g_data->g_mutex));
		return (1);
	}
	pthread_mutex_unlock(&(philo->g_data->g_mutex));
	return (0);
}

char	*is_dead(t_data *data, t_philo *philo)
{
	long long (ti);
	int (i);
	i = 0;
	while (data->dead != 1)
	{
		ti = get_time_ms() - philo->start_time;
		if (data->times_must_eat != 0)
		{
			if (check_meals_and_dead(data, philo, ti, i) == 1)
				return ("done");
			else if (check_meals_and_dead(data, philo, ti, i) == 2)
				return (philo_dead(data, philo, ti, i));
		}
		else
		{
			if (check_dead(data, philo, ti, i) == 1)
				return (philo_dead(data, philo, ti, i));
			if (i + 1 == data->nbr_of_philo)
				i = 0;
			else
				i++;
		}
	}
	return (NULL);
}
