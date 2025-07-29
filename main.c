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

void ft_print(t_philo *philo, char *str)
{
	int i;

	i = 0;	
	pthread_mutex_lock(&philo->write_mutex);

	printf("philo -> %d  is  %s\n", philo->num_philo, str);
	
	pthread_mutex_unlock(&philo->write_mutex);
}


void	ft_putstr_fd(char *s, int fd)
{
	int		i;
	(void)fd;

	i = 0;
	if (s)
	while (s[i])
	{
		write(1, &s[i], 1);
		i++;
	}
}

void *simulation(void *ph)
{
	t_philo *philos;
	// char *str;

	philos = (t_philo *)ph;


	// ft_print(philos, "lunched");
	eating(philos);
	sleeping(philos);
	thinking(philos);

	return(NULL);
}

void thinking(t_philo *philo)
{
	ft_print(philo, "thinking");
}

void sleeping(t_philo *philo)
{
	ft_print(philo, "sleeping");
	ft_usleep(philo->g_data->time_to_sleep);
}

void eating(t_philo *philo)
{
	int f1;
	int f2;

	f1 = philo->left_fork;
	f2 = philo->right_fork;

	pthread_mutex_lock(&philo->forks[f1]);
	pthread_mutex_lock(&philo->forks[f2]);

	ft_print(philo, "take 2 fork");
	ft_print(philo, "eating");

	ft_usleep(philo->g_data->time_to_eat);

	pthread_mutex_unlock(&philo->forks[f1]);
	pthread_mutex_unlock(&philo->forks[f2]);

	ft_print(philo, "drop 2 forks");

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

do in true loop, or nbr_must_eat
is we should just lock mutex without other variabls 

handling time (time_to_die, ...)
*/


// forks just varibales used by threads  eat
// other threads wait  think/sleep

// eat -> use mutex
// sleep -> use usleep
// think -> unused mutex 

