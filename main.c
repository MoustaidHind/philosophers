#include "philo.h"

int error_msg()
{
	printf("Invalid argument\n");
	return(1);
}

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
	args_to_nbrs(data, ac, av); // fill the struct

	


	
	return(0);
}

