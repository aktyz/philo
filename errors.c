/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:28:57 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/07 16:59:44 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	how_to_run(t_data *data);
void	ft_philo_error(t_philo_errors e_nb, t_data *data);

const char	*g_philo_error_messages[NB_ERRORS] = {
	"Your argument is not a philo valid number",
	"Memory allocation error",
	"Provided integer is grater than INT_MAX, please provide smaller number",
	"You provided incorrect number of arguments",
	"Any of the arguments cannot be zero",
	"Failed to initialize the array of mutexes",
	"Values you provided are not allowing for thinking time",
	"Time calculaiton function failed"
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

void	how_to_run(t_data *data)
{
	printf("Incorrect number of arguments!\n");
	printf("Provide four or five arguments:\n");
	printf("nb_of_philosophers\ttime_to_die\ttime_to_eat\ttime_to_sleep\n");
	printf("\nOptional fifth argument:\n");
	printf("nb_of_times_each_philosopher_must_eat\n");
	ft_philo_error(INCORRECT_NB_ARGS, data);
}
