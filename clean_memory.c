#include "philo.h"


int error_msg()
{
	printf("Invalid argument\n");
	return(1);
}


int clean_data(t_data *data)
{
	free(data);
	return(error_msg());
}

