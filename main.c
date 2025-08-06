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

int main(int ac, char *av[])
{
	pthread_mutex_t	*arr_forks;
	pthread_t		*threads;
	t_data			*data;
	t_philo			*philos;
	int i = 0;
	int j = 0;


	// parse the arguments
	if(ac != 5 && ac != 6) // if not the right nbr of args 
		return(error_msg("Invalid argument"));
	if(valide_args(av) == -1) // if all args nbr
		return(error_msg("Invalid argument"));
	data = malloc(sizeof(t_data));
	if(!data)
		return(1);
	if(args_to_nbrs(data, ac, av) == 1) // fill the struct
		return(1);
	if(data->nbr_of_philo == 1)
		return(clean_data(data, "Invalid number of forks")); 
	//leaks handled until here 

	arr_forks = forks(data);
	if(!arr_forks)
		return(clean_data(data, "Bad allocation")); 
	philos = philo_infos(data, arr_forks);
	if(!philos)
		return(free(arr_forks), clean_data(data, "Bad allocation"));  // need to destroy mutexes 

	threads = create_philo(data, philos, arr_forks);  // check NULL
	if(threads == NULL)
	{
		free(philos);
		free(arr_forks);
		free(data);
		// free(threads); // in case dead
		return(1);  // need to distroy mutexes
	}

	
	i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	j = 0;
	while (j++ < data->nbr_of_philo)
		pthread_mutex_destroy(&(arr_forks[j])); // destroy all the the mutex to use it
	free(arr_forks);
	free(philos);
	free(threads);
	free(data);
	return(0);
}

//steps to do
/*

How i should stop all threads after a dead message. a flage to stope simulation.

clean data.
handle leaks.

*/

// 3 310 200 100  -> should die

/* 
	eating    |sleep |  |
|------|------|------|--|----|------|------|------|------

	  100    200    300    400

|------|------|------|------|------|------|------|------
              |    eating   |
			  
	  100    200    300    400

|------|------|------|------|------|------|------|------
              				|    eating   |
*/

/* 
test 5 60 60 60 -> should not print after dead message
*/

/* --> shouldn't die (because i calculate strat time early)
------------test it in linux----------------------
╰─$ ./philo 4 410 200 200                                                                                                                              130 ↵
0 2 has taken a fork
0 2 has taken a fork
0 2 is eating
200 2 is sleeping
200 1 has taken a fork
200 1 has taken a fork
200 1 is eating
400 2 is thinking
399 4 has taken a fork
399 4 has taken a fork
399 4 is eating
400 1 is sleeping
411 3 dead
*/


// why thread 3 come before thread 1 (somtihng about priority ~learn about it~)

