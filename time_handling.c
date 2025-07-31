#include "philo.h"

void ft_usleep(int timing_ms)
{
	int i;
	long long start;
	long long end;

	printf("---->time i get %d\n", timing_ms);
	start = get_time_ms(); 
	// end = get_time_ms(); 
	i = 0;
	while (i < (timing_ms * 10))
	{
		usleep(100);
		i++;
	}

	end = get_time_ms();
	printf("---------------------time spend in usleep %lld\n", end - start);

}

void ft_print(t_philo *philo, long long timestamp, char *str)
{
	pthread_mutex_lock(&philo->write_mutex);

		// timestamp_in_ms X has taken a fork
	// long long curr_time;

	// curr_time = get_time_ms() - timestamp;
	printf("%lld %d %s\n", timestamp, philo->num_philo, str);
	
	pthread_mutex_unlock(&philo->write_mutex);
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
	// printf("time in ms %d\n", millisec);

	return (millisec);
}

