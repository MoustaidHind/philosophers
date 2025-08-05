/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_memory.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: himousta <himousta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 16:58:46 by himousta          #+#    #+#             */
/*   Updated: 2025/08/05 16:58:48 by himousta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

