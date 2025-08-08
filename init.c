/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:58:58 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:59 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int				j;

	j = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if (!forks)
		return (NULL);
	while (j < data->nbr_of_philo)
	{
		pthread_mutex_init(&(forks[j]), NULL);
		j++;
	}
	return (forks);
}

t_philo	*philo_infos(t_data *data, pthread_mutex_t *arr_forks)
{
	t_philo			*philos;
	int				i;

	i = 0;
	philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if (!philos)
		return (NULL);
	while (i < data->nbr_of_philo)
	{
		philos[i].num_philo = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->nbr_of_philo;
		philos[i].last_time_eat = 0;
		philos[i].start_time = 0;
		philos[i].g_data = data;
		philos[i].forks = arr_forks;
		pthread_mutex_init(&(philos->write_mutex), NULL);
		i++;
	}
	return (philos);
}

int	create_odd_even_philos(t_data *data, t_philo *philos, pthread_t *threads)
{
	long long	(initial_time);
	int	(i), (re);
	i = 0;
	initial_time = get_time_ms();
	while (i < data->nbr_of_philo)
	{
		philos[i].start_time = initial_time;
		re = pthread_create(&threads[i], NULL, simulation, \
			(void *)&(philos[i]));
		if (re != 0)
			return (printf("pthread fail\n"), -1);
		i += 2;
	}
	usleep(100);
	i = 1;
	while (i < data->nbr_of_philo)
	{
		philos[i].start_time = initial_time;
		re = pthread_create(&threads[i], NULL, simulation, \
			(void *)&(philos[i]));
		if (re != 0)
			return (printf("pthread fail\n"), -1);
		i += 2;
	}
	return (0);
}

pthread_t	*create_philo(t_data *data, t_philo *philo, pthread_mutex_t *forks)
{
	pthread_t	*threads;

	threads = malloc(sizeof(pthread_t) * data->nbr_of_philo);
	if (!threads)
	{
		clean_up(philo, forks, threads);
		return (printf("Bad allocation\n"), NULL);
	}
	if (create_odd_even_philos(data, philo, threads) == -1)
		return (clean_up(philo, forks, threads), NULL);
	usleep(1000);
	if (!is_dead(data, philo))
		return (clean_up(philo, forks, threads), NULL);
	return (threads);
}
