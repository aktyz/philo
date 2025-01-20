/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 15:40:49 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *param);
void		*waiter_routine(void *param);

void	*philo_routine(void *param)
{
	t_philo_r	*args;
	t_philo		*philo;
	t_args		*info;
	
	args = (t_philo_r *) param;
	philo = args->philo;
	info = args->info;
	while (1) //TODO: how to get out of this loop -> waiter thread mechanism
	{
		philo_take_forks(philo, info);
		philo_eat(philo, info);
		philo_put_down_forks(philo);
		philo->meal_nb++;
		philo_sleep(philo, info);
		philo_think(philo, info);
	}
	free(args);
	return (NULL);
}

void	*waiter_routine(void *param)
{
	(void) param;
	return (NULL);
}
