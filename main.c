#include "philo.h"

int main(int ac, char *av[])
{
	pthread_mutex_t	*arr_forks;
	pthread_t		*threads;
	t_data			*data;
	t_philo			*philos;
	// long long		current_time;

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
	philos = philo_infos(data, arr_forks); // check NULL
	threads = create_philo(data, philos);  // check NULL

	// get_time_ms(); // get current time in ms instead of microsec


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

do in true loop, or nbr_must_eat ~~~
is we should just lock mutex without other variabls 

understand ~~~
( 4 310 200 100 ) died 
( 4 410 200 200 )  not died 

do ~~~~
0ms
200ms
300ms ....

handling time (time_to_die, ...)

check if a phio die . (try to catche die philo)


*/
