#include "philo.h"


void ft_usleep(int timing_ms)
{
	int i;

	i = 0;
	while (i < (timing_ms * 10))
	{
		usleep(100);
		i++;
	}
}

// void ft_print(t_philo *philo, char *str)
// {
// 	int i;
// 	int len;

// 	i = 0;
// 	len = ft_strlen(str);
	
	
// 	write(1, str, len);
// }

void *simulation(void *ph)
{
	t_philo *philos;

	philos = (t_philo *)ph;
	
	pthread_mutex_lock(&philos->write_mutex);
	printf("im philo = %d, ", philos->num_philo);
	printf("left_fork = %d, ", philos->left_fork);
	printf("right_fork = %d,", philos->right_fork);
	pthread_mutex_unlock(&philos->write_mutex);

	eat(philos);
	ft_sleep(philos);
	think();

	return(NULL);
}

void think()
{
	write(1, "is thinking\n", 12);
}

void ft_sleep(t_philo *philo)
{
	pthread_mutex_lock(&philo->write_mutex);
	write(1, "is sleeping\n", 12);
	pthread_mutex_unlock(&philo->write_mutex);

	ft_usleep(philo->g_data->time_to_sleep);
}

void eat(t_philo *philo)
{
	int f1;
	int f2;

	f1 = philo->left_fork;
	f2 = philo->right_fork;

	pthread_mutex_lock(&philo->forks[f1]);
	pthread_mutex_lock(&philo->forks[f2]);

	pthread_mutex_lock(&philo->write_mutex);

	printf("i take 2 fork \n"); // use write instead
	printf("im eating\n");

	ft_usleep(philo->g_data->time_to_eat);

	pthread_mutex_unlock(&philo->forks[f1]);
	pthread_mutex_unlock(&philo->forks[f2]);

	printf("i drop 2 forks\n");

	pthread_mutex_unlock(&philo->write_mutex);
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
	philos = philo_infos(data, arr_forks); // check NULL
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

implement simple actions 
eat ~~
sleep
think

handling time
*/


// forks just varibales used by threads  eat
// other threads wait  think/sleep

// eat -> use mutex
// sleep -> use usleep
// think -> unused mutex 

