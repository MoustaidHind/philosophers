/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:59:43 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:59:48 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void ft_usleep(int timing_ms)
{
	long long start;

	start = get_time_ms();
	while ((get_time_ms() - start) < timing_ms) // 0 < 200 * 10 = 2000 * 100 = 20 000 (microsec)
		usleep(100); //awake every 0.1ms to check the time (to dont oversleep)
}

void ft_print(t_philo *philo, long long timestamp, char *str)
{
	pthread_mutex_lock(&(philo->g_data->dead_mutexx));

	if(philo->g_data->dead != 1)
		printf("%lld %d %s\n", timestamp, philo->num_philo, str);
	
	pthread_mutex_unlock(&(philo->g_data->dead_mutexx));
}

long long get_time_ms() // get current time in ms instead of microsec
{
	struct timeval	tv;
	int				millisec;

	if(gettimeofday(&tv, NULL) == -1)
	{
		printf("get time of day fail\n");
		return (-1);
	}
	millisec = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (millisec);
}

