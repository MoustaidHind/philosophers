
#include "philo.h"

int is_number(char *str)
{
	int i;

	i = 0;
	if(!str[i])
		return(-1);
	while (str[i])
	{
		if(str[i] < '0' || str[i] > '9')
			return(-1);
		i++;
	}
	return(0);
}

int valide_args(char **av)
{
	int i;
	
	i = 1; //to skip name program
	while (av[i])
	{
		if(is_number(av[i]) == -1)
			return(-1);
		i++;
	}
	return(0);
}

void clean_data(t_data *data)
{
	free(data);
	error_msg();
}

void args_to_nbrs(t_data *data, int ac, char **av)
{
	data->nbr_of_philo = ft_atoi(av[1]);
	if(data->nbr_of_philo == -1)
		clean_data(data);
	data->time_to_die = ft_atoi(av[2]);
	if(data->time_to_die == -1)
		clean_data(data);
	data->time_to_eat = ft_atoi(av[3]);
	if(data->time_to_eat == -1)
		clean_data(data);
	data->time_to_sleep = ft_atoi(av[4]);
	if(data->time_to_sleep == -1)
		clean_data(data);
	data->times_must_eat = 0;
	if(ac == 6)
	{
		data->times_must_eat = ft_atoi(av[5]);
		if(data->times_must_eat == -1)
			clean_data(data);
	}
}
