/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:28:57 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/06 19:12:28 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char	*g_philo_error_messages[NB_ERRORS] = {
	"Your argument is not a philo valid number",
	"Memory allocation error",
	"Provided integer is grater than INT_MAX, please provide smaller number",
	"You provided incorrect number of arguments",
	"Any of the arguments cannot be zero",
	"Failed to initialize the array of mutexes",
	"Values you provided are not allowing for thinking time"
};

void	ft_philo_error(t_philo_errors e_nb, t_data *data)
{
	set_bool(&data->data_mutex, data->is_end, true);
	if (e_nb < 0 || e_nb >= NB_ERRORS)
	{
		printf("Unknown error!\n");
		return ;
	}
	printf("Error: %s\n", g_philo_error_messages[e_nb]);
	return ;
}
