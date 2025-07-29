#include "philo.h"

typedef struct philo
{
	int num_philo;
	int left_fork; // index in the mutex array
	int right_fork;
	t_data *g_data;

} t_philo;

void *simulation(void *ph)
{
	t_philo *philos;

	philos = (t_philo *)ph;

	printf("im philo = %d  ", philos->num_philo);
	printf("left = %d  ", philos->left_fork);
	printf("right = %d  \n", philos->right_fork);

	return(NULL);
}

pthread_mutex_t *forks(t_data *data)
{
	pthread_mutex_t	*forks;

	// create array of mutexes
	forks = malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	if(!forks)
		return(NULL);
	int j = 0;
	while (j < data->nbr_of_philo)
	{
		pthread_mutex_init(&(forks[j]), NULL); // initialize all the the mutex to use it
		j++;
	}
	
	return(forks);
}

t_philo *philo_infos(t_data *data)
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


int main(int ac, char *av[])
{
	pthread_mutex_t	*arr_forks;
	pthread_t		*threads;
	t_data			*data;
	t_philo			*philos;

	// parse the arguments
	if(ac != 5 && ac != 6) // if not the right nbr of args 
		return(error_msg());
	if(valide_args(av) == -1) // if all args nbr
		return(error_msg());
	data = malloc(sizeof(t_data));
	if(!data)
		return(1);
	if(args_to_nbrs(data, ac, av) == 1) // fill the struct
		return(1);
	
	arr_forks = forks(data); // check NULL
	philos = philo_infos(data); // check NULL
	threads = create_philo(data, philos);  // check NULL

	int i = 0;
	while (i < data->nbr_of_philo)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	int j = 0;
	while (j++ < data->nbr_of_philo)
		pthread_mutex_destroy(&(arr_forks[j])); // initialize all the the mutex to use it
	free(data);
	return(0);
}

//steps to do
/*
creat threads (philos) ~~~
creat array of mutex (forks) (form 0 to nbr) (initialize mutex) ~~~

Create philosophers and assign: ~~~
    ID
    Left and right fork index
    Pointer to the shared data
Print each philosopher’s ID and fork indexes


handling time
*/


// forks just varibales used by threads  eat
// other threads wait  think/sleep

// eat -> use mutex
// sleep -> use usleep
// think -> unused mutex 

