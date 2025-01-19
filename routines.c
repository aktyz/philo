/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/19 16:42:03 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *param);

void	*philo_routine(void *param)
{
	t_philo_r	*args;
	
	args = (t_philo_r *) param;
	/**while (all_alive) //TODO: how to do it...
	{
		philo_takes_fork(args->philo->first_fork); //take first fork
		philo_takes_fork(args->philo->second_fork); //take second fork
		philo_eat(args->philo, args->info->eat_time);
		philo_put_down_fork(args->philo->first_fork);
		philo_put_down_fork(args->philo->second_fork);
		args->philo->meal_nb++;
		philo_sleep(args->philo, args->info->sleep_time);
		philo_think(args->philo);
	}*/
	free(args);
	return (NULL);
}
