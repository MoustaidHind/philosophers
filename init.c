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
		philos[i].num_philo = i;
		philos[i].left_fork = i;
		philos[i].right_fork = (i + 1) % data->nbr_of_philo; 
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

	i = 0;
	// creat array of ids_threads
	threads = malloc(sizeof(pthread_t) * data->nbr_of_philo);  // check l fail
	while (i < data->nbr_of_philo)
	{
		re = pthread_create(&threads[i], NULL, simulation, (void *)&(philos[i])); //pass address of element of the array
		if(re != 0)
			printf("pthread fail");
		i++;
	}

	return(threads);
}

