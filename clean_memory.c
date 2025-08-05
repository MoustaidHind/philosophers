#include "philo.h"


int error_msg(char *str)
{
	printf("%s\n", str);
	return(1);
}


int clean_data(t_data *data, char *str)
{
	free(data);
	return(error_msg(str));
}

