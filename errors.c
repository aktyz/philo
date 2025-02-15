/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:28:57 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/15 19:57:31 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				ft_philo_error(t_philo_errors e_nb, t_data *data);
void				ft_philo_instruct(void);
static const char	**get_philo_error_messages(void);

/**
 * Function prints error message on program exit
 *
 */
void	ft_philo_error(t_philo_errors e_nb, t_data *data)
{
	if (e_nb == NO_ERROR)
		return ;
	if (e_nb > 4)
	{
		pthread_mutex_lock(&data->data_mutex);
		data->is_error = e_nb;
		data->is_sym_ended = true;
		pthread_mutex_unlock(&data->data_mutex);
	}
	else
	{
		data->is_error = e_nb;
		data->is_sym_ended = true;
	}
	if (e_nb < 0 || e_nb >= NB_ERRORS)
		printf("Unknown error!\n");
	else
		printf("Error: %s\n", get_philo_error_messages()[e_nb]);
	return ;
}

/**
 * Function instructing how to run philo program in case user
 * provided wrong arguments
 *
 */
void	ft_philo_instruct(void)
{
	printf("Incorrect number of arguments!\n");
	printf("Provide four or five arguments:\n");
	printf("nb_of_philosophers\ttime_to_die\ttime_to_eat\ttime_to_sleep\n");
	printf("\nOptional fifth argument:\n");
	printf("nb_of_times_each_philosopher_must_eat\n");
}

/**
 * As I cannot use global variables, this function returns a string array,
 * containing necessary error messages when something fails
 *
 */
static const char	**get_philo_error_messages(void)
{
	static const char	*e_msg[NB_ERRORS];

	e_msg[1] = "Your argument is not a philo valid number";
	e_msg[2] = "Provided integer is greater than INT_MAX";
	e_msg[3] = "Memory allocation error";
	e_msg[4] = "Failed to initialize data protection mutex";
	e_msg[5] = "Failed to initialize mutex";
	e_msg[6] = "Time calculation function failed";
	e_msg[7] = "Failed to initialize thread";
	return (e_msg);
}
