#include "philo.h"


int main(int ac, char *av[])
{
	t_data *data;

	if(ac != 5 && ac != 6) // if not the right nbr of args 
		return(error_msg());
	if(valide_args(av) == -1) // if all args nbr
		return(error_msg());
	data = malloc(sizeof(t_data));
	if(!data)
		return(1);
	if(args_to_nbrs(data, ac, av) == 1) // fill the struct
		return(1);
	

	
	free(data);
	return(0);
}

//steps to do
/*
creat threads (philos)
creat array of mutex (forks) (form 0 to 1) (initialize mutex )
save nbr of left and right forks for each philo 

handling time 

*/


// forks just varibales used by threads  eat
// other threads wait  think/sleep

// eat -> use mutex
// sleep -> use usleep
// think -> unused mutex 

