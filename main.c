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

	if (ac != 5 && ac != 6)
		return (error_msg("Invalid argument"), NULL);
	if (valide_args(av) == -1)
		return (error_msg("Invalid argument"), NULL);
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	if (args_to_nbrs(data, ac, av) == 1)
		return (NULL);
	return (data);
}

char	*is_dead(t_data *data, t_philo *philo, long long start_time)
{
	long long	ti;
	int			i;

	start_time = get_time_ms();
	if (start_time == -1)
		return (NULL);
	i = 0;
	while (data->dead != 1)
	{
		ti = get_time_ms() - start_time;
		if ((ti - philo[i].last_time_eat) >= data->time_to_die)
		{
			pthread_mutex_lock(&(data->dead_mutexx));
			data->dead = 1;
			pthread_mutex_unlock(&(data->dead_mutexx));
			printf("%lld %d %s\n", ti, philo[i].num_philo, "dead");
			return (NULL);
		}
		if (i + 1 == data->nbr_of_philo)
			i = 0;
		else
			i++;
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
