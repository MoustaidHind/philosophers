/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:11 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:13 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_zero_nbr(t_data *data, int ac)
{
	if (ac == 6)
		if (data->times_must_eat == 0)
			return (clean_data(data, "Invalid argument"));
	if (data->nbr_of_philo == 0 || data->time_to_die == 0 \
		|| data->time_to_eat == 0 || data->time_to_sleep == 0)
		return (clean_data(data, "Invalid argument"));
	return (0);
}

t_data	*parssing_part(int ac, char *av[])
{
	t_data			*data;

	if (ac != 5 && ac != 6)
		return (error_msg("Invalid argument"), NULL);
	if (valide_args(av) == -1)
		return (error_msg("Invalid argument"), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (args_to_nbrs(data, ac, av) == 1)
		return (NULL);
	if (check_zero_nbr(data, ac) == 1)
		return (NULL);
	return (data);
}

char	*philo_dead(t_data *data, t_philo *philo, long long time, int i)
{
	pthread_mutex_lock(&(data->dead_mutexx));
	data->dead = 1;
	pthread_mutex_unlock(&(data->dead_mutexx));
	printf("%lld %d %s\n", time, philo[i].num_philo, "dead");
	return (NULL);
}

char	*is_dead(t_data *data, t_philo *philo)
{
	long long (ti);
	int (i);
	i = 0;
	while (data->dead != 1)
	{
		ti = get_time_ms() - philo->start_time;
		if(data->times_must_eat != 0)
		{
			pthread_mutex_lock(&(philo->g_data->g_mutex));
			if ((ti - philo[i].last_time_eat) >= data->time_to_die)// need to protect with mutex
			{
				pthread_mutex_unlock(&(philo->g_data->g_mutex));
				pthread_mutex_lock(&(philo->g_data->many_times_eat_mutexx));
				if (data->many_times_eat == (data->nbr_of_philo * data->times_must_eat))
				{
					pthread_mutex_unlock(&(philo->g_data->many_times_eat_mutexx));
					return ("done");
				}
				pthread_mutex_unlock(&(philo->g_data->many_times_eat_mutexx));
				return(philo_dead(data, philo, ti, i));	
			}
			pthread_mutex_unlock(&(philo->g_data->g_mutex));
		}
		else
		{
			pthread_mutex_lock(&(philo->g_data->g_mutex));
			if ((ti - philo[i].last_time_eat) >= data->time_to_die) // need to protect with mutex
			{
				pthread_mutex_unlock(&(philo->g_data->g_mutex));
				return(philo_dead(data, philo, ti, i));
			}
			pthread_mutex_unlock(&(philo->g_data->g_mutex));
			if (i + 1 == data->nbr_of_philo)
				i = 0;
			else
				i++;
		}
	}
	return (NULL);
}

int	main(int ac, char *av[])
{
	pthread_mutex_t	*arr_forks;
	pthread_t		*threads;
	t_data			*data;
	t_philo			*philos;

	data = parssing_part(ac, av);
	if (!data)
		return (1);
	arr_forks = forks(data);
	if (!arr_forks)
		return (clean_data(data, "Bad allocation"));
	philos = philo_infos(data, arr_forks);
	if (!philos)
		return (free(arr_forks), clean_data(data, "Bad allocation"));
	threads = create_philo(data, philos, arr_forks);
	if (threads == NULL)
		return (1);
	clean_up(philos, arr_forks, threads);
	return (0);
}

/*
is a philo should die when find time_die == curr_time
*/

/*
Protect shared variables

Protect all reads/writes to:

    philo->last_meal

    philo->eat_count

    philo->g_data->dead
*/