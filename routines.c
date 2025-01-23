/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/23 20:26:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *param);
bool		is_nb_meals(t_args **info, t_philo **philo);
bool		is_starved(t_args **info, t_philo **philo);
void		*waiter_routine(void *param);

void	*philo_routine(void *param)
{
	t_philo_r	*args;
	t_philo		*philo;
	t_args		*info;
	
	args = (t_philo_r *) param;
	philo = args->philo;
	info = args->info;
	while (!is_starved(&info, &philo) || !is_nb_meals(&info, &philo))
	{
		philo_take_forks(philo, info);
		if (!is_starved(&info, &philo))
		{
			philo_eat(philo, info);
			philo_put_down_forks(philo);
			philo->meal_nb++;
			philo_sleep(philo, info);
			philo_think(philo, info);
		}
		else
			break;
	}
	free(args);
	return (NULL);
}

void	*waiter_routine(void *param)
{
	t_waiter_r	*args;

	args = (t_waiter_r *) param;
	while (1)
	{
		pthread_mutex_lock(&args->info->info_mutex);
		if (args->info->is_terminated)
			break;
		pthread_mutex_unlock(&args->info->info_mutex);
	}
	return (NULL);
}

bool	is_nb_meals(t_args **info, t_philo **philo)
{
	if ((*info)->min_nb_meals && (*philo)->meal_nb == (*info)->min_eat)
	{
		pthread_mutex_lock(&(*info)->info_mutex);
		(*info)->is_terminated = true;
		pthread_mutex_unlock(&(*info)->info_mutex);
		return (1);
	}
	else
		return (0);
}

bool	is_starved(t_args **info, t_philo **philo)
{
	s_timeval	time_stamp;
	int			difference;
	bool		is_starved;

	gettimeofday(&time_stamp, NULL);
	difference = convert_to_miliseconds(subtract_timeval(time_stamp, (*philo)->meal_start_time));
	is_starved = difference > (*info)->die_time;
	if (is_starved)
	{
		pthread_mutex_lock(&(*info)->info_mutex);
		(*info)->is_terminated = true;
		printf("%d %d died\n", difference, (*philo)->philo_nb);
		return (1);
	}
	else
	{
		(*philo)->meal_start_time.tv_sec = time_stamp.tv_sec;
		(*philo)->meal_start_time.tv_usec = time_stamp.tv_usec;
		return (0);
	}
}
