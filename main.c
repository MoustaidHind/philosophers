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

t_data	*parssing_part(int ac, char *av[])
{
	t_data			*data;

	if(ac != 5 && ac != 6) // if not the right nbr of args 
		return(error_msg("Invalid argument"), NULL);
	if(valide_args(av) == -1) // if all args nbr
		return(error_msg("Invalid argument"), NULL);
	data = malloc(sizeof(t_data));
	if(!data)
		return(NULL);
	if(args_to_nbrs(data, ac, av) == 1) // fill the struct
		return(NULL);
	return(data);
}

int main(int ac, char *av[])
{
	pthread_mutex_t	*arr_forks;
	pthread_t		*threads;
	t_data			*data;
	t_philo			*philos;

	data = parssing_part(ac, av);
	if(!data)
		return(1);
	arr_forks = forks(data);
	if(!arr_forks)
		return(clean_data(data, "Bad allocation")); 
	philos = philo_infos(data, arr_forks);
	if(!philos)
		return(free(arr_forks), clean_data(data, "Bad allocation"));  // need to destroy mutexes 
	threads = create_philo(data, philos, arr_forks);  // check NULL
	if(threads == NULL)
		return(1);
	clean_up(philos, arr_forks, threads);
	return(0);
}



// why thread 3 come before thread 1 (somtihng about priority ~learn about it~)

// distory mutex i use (dead, write ...)