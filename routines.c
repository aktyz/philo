/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 19:03:32 by zslowian         ###   ########.fr       */
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
	s_timeval	time_stamp;
	
	args = (t_philo_r *) param;
	philo = args->philo;
	info = args->info;
	while (philo->philo_status != DEAD || info->is_terminated != true) // TODO: figure out where and how to check the variables in order to end the program in the right place
	{
		if (info->min_nb_meals && philo->meal_nb == info->min_eat)
			break ;
		philo_take_forks(philo, info);
		gettimeofday(&time_stamp, NULL);
		if (convert_to_miliseconds(subtract_timeval(time_stamp, philo->meal_start_time))
			> info->die_time)
		{
			philo->philo_status = DEAD;
			gettimeofday(&time_stamp, NULL);
			pthread_mutex_lock(&info->print); // TODO: nothing more will be printed but what about the treads hanging on this lock - how to move them from there
			die(convert_to_miliseconds(subtract_timeval(info->start_time, time_stamp)), philo->philo_nb, &info->print);
			break ;
		}
		else
		{
			philo->meal_start_time.tv_sec = time_stamp.tv_sec;
			philo->meal_start_time.tv_usec = time_stamp.tv_usec;
		}
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
	t_waiter_r	*args;
	int			i;

	args = (t_waiter_r *) param;
	while (1)
	{
		i = 0;
		while (i < args->info->nb_philos)
		{
			if (args->philos[i].philo_status == DEAD)
			{
				args->info->is_terminated = true; // TODO: add a mutex on this variable
			}
			i++;
		}
	}
	return (NULL);
}
