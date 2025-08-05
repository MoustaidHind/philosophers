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

	int j = 0;

	// create array of mutexes
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

pthread_t		*create_philo(t_data *data, t_philo *philos)
{
	pthread_t		*threads;
	int				re;
	int				i;
	long long 	start_time;

	i = 0;
	// creat array of ids_threads
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philo);
	if(!threads)
		return(printf("Bad allocation\n"), NULL);

	start_time = get_time_ms();
	if(start_time == -1)
		return(free(threads), NULL);

	while (i < data->nbr_of_philo) // start the even threads, index(0, 2, 4, 6) -> thread(1, 3, 5, 7)
	{
		re = pthread_create(&threads[i], NULL, simulation, (void *)&(philos[i])); //pass address of element of the array
		if(re != 0)
			return(free(threads), printf("pthread fail\n"), NULL);
		i += 2;
	}
	i = 1;  // start from 1
	while (i < data->nbr_of_philo) // start the odd threads, index(1, 3, 5, 7) -> thread(2, 4, 6, 8)
	{
		re = pthread_create(&threads[i], NULL, simulation, (void *)&(philos[i])); //pass address of element of the array
		if(re != 0)
			return(free(threads), printf("pthread fail\n"), NULL);
		i += 2;
	}

	if(!is_dead(data, philos, start_time))
		return(free(threads), NULL);
	return(threads);
}


char *is_dead(t_data *data, t_philo *philo, long long start_time)
{
	long long ti;
	int i;
	int dead = 0;
	
	start_time = get_time_ms();
	if(start_time == -1)
		return(NULL);

	i = 0;
	while (dead != 1)
	{
		ti = get_time_ms() - start_time;
		if((ti - philo[i].last_time_eat) >= data->time_to_die) 
		{
			dead = 1; // not valid
			ft_print(&philo[i], ti, "dead");
			return(NULL);
		}
		if(i + 1 == data->nbr_of_philo)
			i = 0;
		else
			i++;
		ft_usleep(5);
	}
	return(NULL);
}

