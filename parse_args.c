/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:18 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:19 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	is_number(char *str)
{
	int	i;

	i = 0;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (-1);
		i++;
	}
	return (0);
}

int	valide_args(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (is_number(av[i]) == -1)
			return (-1);
		i++;
	}
	return (0);
}

int	args_to_nbrs(t_data *data, int ac, char **av)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	if (data->nbr_of_philo == -1)
		return (clean_data(data, "atoi failed"));
	data->time_to_die = ft_atoi(av[2]);
	if (data->time_to_die == -1)
		return (clean_data(data, "atoi failed"));
	data->time_to_eat = ft_atoi(av[3]);
	if (data->time_to_eat == -1)
		return (clean_data(data, "atoi failed"));
	data->time_to_sleep = ft_atoi(av[4]);
	if (data->time_to_sleep == -1)
		return (clean_data(data, "atoi failed"));
	data->times_must_eat = 0;
	data->many_times_eat = 0;
	data->dead = 0;
	pthread_mutex_init(&(data->g_mutex), NULL);
	pthread_mutex_init(&(data->many_times_eat_mutexx), NULL);
	pthread_mutex_init(&(data->dead_mutexx), NULL);
	if (ac == 6)
	{
		data->times_must_eat = ft_atoi(av[5]);
		if (data->times_must_eat == -1)
			return (clean_data(data, "atoi failed"));
	}
	return (0);
}
