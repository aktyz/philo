/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 14:43:04 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *param);
void		*waiter_routine(void *param);

void	*philo_routine(void *param)
{
	t_philo_r	*args;
	t_philo		*philo;
	
	args = (t_philo_r *) param;
	philo = args->philo;
	while (1) //TODO: how to get out of this loop -> waiter thread mechanism
	{
		philo_take_forks(philo, args->info->start_time);
		philo_eat(philo, args->info->eat_time, args->info->start_time);
		philo_put_down_forks(philo);
		philo->meal_nb++;
		philo_sleep(philo, args->info->sleep_time, args->info->start_time);
		philo_think(philo, args->info->start_time, args->info->max_think_time);
	}
	free(args);
	return (NULL);
}

void	*waiter_routine(void *param)
{
	(void) param;
	return (NULL);
}
