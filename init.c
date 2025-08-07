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

pthread_mutex_t *forks(t_data *data)
{
	pthread_mutex_t	*forks;
	int j;

	// create array of mutexes
	j = 0;
	forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if(!forks)
		return(NULL);
	while (j < data->nbr_of_philo)
	{
		pthread_mutex_init(&(forks[j]), NULL); // initialize all the the mutex to use it
		j++;
	}
	return(forks);
}

t_philo *philo_infos(t_data *data, pthread_mutex_t *arr_forks)
{
	t_philo			*philos;
	int 			i;

	i = 0;
	// create array of structs t_philo to fill with infos
	philos = malloc(sizeof(t_philo) * data->nbr_of_philo);
	if(!philos)
		return(NULL);
	while (i < data->nbr_of_philo)
	{
		philos[i].num_philo = i + 1;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->nbr_of_philo; 
		philos[i].last_time_eat = 0;
		philos[i].g_data = data;
		philos[i].forks = arr_forks;
		pthread_mutex_init(&(philos->write_mutex), NULL);
		i++;
	}
	return (philos);
}

int		create_odd_even_philos(t_data	*data, t_philo	*philos, pthread_t	*threads)
{
	int i;
	int re;

	i = 0;
	while (i < data->nbr_of_philo) // start the even threads, index(0, 2, 4, 6) -> thread(1, 3, 5, 7)
	{
		re = pthread_create(&threads[i], NULL, simulation, (void *)&(philos[i])); //pass address of element of the array
		if(re != 0)
			return(printf("pthread fail\n"), -1);
		i += 2;
	}
	i = 1;  // start from 1
	while (i < data->nbr_of_philo) // start the odd threads, index(1, 3, 5, 7) -> thread(2, 4, 6, 8)
	{
		re = pthread_create(&threads[i], NULL, simulation, (void *)&(philos[i])); //pass address of element of the array
		if(re != 0)
			return(printf("pthread fail\n"), -1);
		i += 2;
	}
	return(0);
}

void clean_up(t_philo *philos, pthread_mutex_t	*arr_forks, pthread_t	*threads)
{
	int i;

	i = 0;
	while (i < philos->g_data->nbr_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	i = 0;
	while (i < philos->g_data->nbr_of_philo)
	{
		pthread_mutex_destroy(&(arr_forks[i])); // destroy all the the mutex to use it
		i++;
	}
	pthread_mutex_destroy(&(philos->g_data->dead_mutexx));
	pthread_mutex_destroy(&(philos->write_mutex));
	if(threads)
		free(threads);
	free(arr_forks);
	free(philos->g_data);
	free(philos);
}


pthread_t		*create_philo(t_data *data, t_philo *philos, pthread_mutex_t	*arr_forks)
{
	pthread_t		*threads;
	long long 	start_time;
	
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philo);
	if(!threads)
	{
		clean_up(philos, arr_forks, threads);
		return(printf("Bad allocation\n"), NULL);
	}
	start_time = get_time_ms();
	if(start_time == -1)
		return(clean_up(philos, arr_forks, threads), NULL);
	if(create_odd_even_philos(data, philos, threads) == -1)
		return(clean_up(philos, arr_forks, threads), NULL);
	if(!is_dead(data, philos, start_time))
		return(clean_up(philos, arr_forks, threads), NULL);
	return(threads);
}


char *is_dead(t_data *data, t_philo *philo, long long start_time)
{
	long long ti;
	int i;
	
	start_time = get_time_ms();
	if(start_time == -1)
		return(NULL);
	i = 0;
	while (data->dead != 1)
	{
		ti = get_time_ms() - start_time;
		if((ti - philo[i].last_time_eat) >= data->time_to_die) 
		{
			pthread_mutex_lock(&(data->dead_mutexx));
			data->dead = 1; // not valid
			pthread_mutex_unlock(&(data->dead_mutexx));
			printf("%lld %d %s\n", ti, philo[i].num_philo,  "dead");

			return(NULL);
		}
		if(i + 1 == data->nbr_of_philo)
			i = 0;
		else
			i++;
	}
	return(NULL);
}

