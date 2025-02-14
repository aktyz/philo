/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:28:57 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 14:03:23 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				how_to_run(t_data *data);
void				ft_philo_error(t_philo_errors e_nb, t_data *data);

static const char	**get_philo_error_messages(void)
{
	static const char	*e_msg[NB_ERRORS];

	e_msg[0] = "Your argument is not a philo valid number";
	e_msg[1] = "Memory allocation error";
	e_msg[2] = "Provided integer is greater than INT_MAX";
	e_msg[3] = "You provided an incorrect number of arguments";
	e_msg[4] = "Any of the arguments cannot be zero";
	e_msg[5] = "Failed to initialize the array of mutexes";
	e_msg[6] = "Values you provided are not allowing for thinking time";
	e_msg[7] = "Time calculation function failed";
	return (e_msg);
}

void	ft_philo_error(t_philo_errors e_nb, t_data *data)
{
	set_bool(&data->data_mutex, &data->is_anyone_dead, true);
	if (e_nb < 0 || e_nb >= NB_ERRORS)
	{
		printf("Unknown error!\n");
		return ;
	}
	printf("Error: %s\n", get_philo_error_messages()[e_nb]);
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
