/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:58:46 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:48 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	error_msg(char *str)
{
	printf("%s\n", str);
	return (1);
}

int	clean_data(t_data *data, char *str)
{
	free(data);
	return (error_msg(str));
}

void	clean_up(t_philo *philo, pthread_mutex_t *arr_forks, pthread_t *thread)
{
	int	i;

	i = 0;
	while (i < philo->g_data->nbr_of_philo)
	{
		pthread_join(thread[i], NULL);
		i++;
	}
	i = 0;
	while (i < philo->g_data->nbr_of_philo)
	{
		pthread_mutex_destroy(&(arr_forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(philo->g_data->dead_mutexx));
	pthread_mutex_destroy(&(philo->g_data->many_times_eat_mutexx));
	pthread_mutex_destroy(&(philo->write_mutex));
	if (thread)
		free(thread);
	free(arr_forks);
	free(philo->g_data);
	free(philo);
}
