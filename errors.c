/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 18:28:57 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/13 17:45:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

const char *philo_error_messages[NB_ERRORS] = {
	"Your argument is not a number",
	"Memory allocation error",
	"Provided integer is grater than INT_MAX, please provide smaller number",
	"You provided incorrect number of arguments",
	"Any of the arguments cannot be zero"
};

void	ft_philo_error(t_philo_errors e_nb)
{
	if (e_nb < 0 || e_nb >= NB_ERRORS)
	{
		printf("Unknown error!\n");
		return ;
	}
	printf("Error: %s\n", philo_error_messages[e_nb]);
}
