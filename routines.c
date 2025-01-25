/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 19:42:47 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/25 21:49:48 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		*philo_routine(void *param);
bool		is_nb_meals(t_args **info, t_philo **philo);
bool		is_starved(t_args **info, t_philo **philo, pthread_mutex_t **philo_lock);

void	*philo_routine(void *param)
{
	t_philo_r		*args;
	t_philo			*philo;
	t_args			*info;
	pthread_mutex_t	*lock;
	s_timeval		program_start;
	bool			is_terminated;

	args = (t_philo_r *) param;
	philo = args->philo;
	info = args->info;
	lock = &args->philo_lock;
	pthread_mutex_lock(&info->info_mutex);
	program_start.tv_sec = info->program_start_time.tv_sec;
	program_start.tv_usec = info->program_start_time.tv_usec;
	is_terminated = info->is_terminated;
	while ((!is_starved(&info, &philo, &lock) || !is_nb_meals(&info, &philo)) && !is_terminated)
	{
		philo_take_forks(philo, program_start, &info->info_mutex);
		if (!pthread_mutex_lock(&info->info_mutex) && !is_starved(&info, &philo, &lock))
		{
			pthread_mutex_lock(lock);
			philo_eat(philo, program_start, &info->info_mutex, philo->eat_time);
			philo_put_down_forks(philo);
			philo->meal_nb++;
			philo_sleep(philo, program_start, &info->info_mutex, philo->sleep_time);
			philo_think(philo, program_start, &info->info_mutex, philo->max_think_time);
			pthread_mutex_unlock(lock);
		}
		else
		{
			pthread_mutex_unlock(lock);
			break;
		}
	}
	free(args);
	return (NULL);
}

bool	is_nb_meals(t_args **info, t_philo **philo)
{
	int	meal_nb;

	meal_nb = (*philo)->meal_nb;
	pthread_mutex_lock(&(*info)->info_mutex);
	if ((*info)->min_nb_meals && meal_nb == (*info)->min_eat)
	{
		(*info)->is_terminated = true;
		pthread_mutex_unlock(&(*info)->info_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&(*info)->info_mutex);
		return (0);
	}
}

bool	is_starved(t_args **info, t_philo **philo, pthread_mutex_t **philo_lock)
{
	s_timeval	time_stamp;
	int			difference;
	bool		is_starved;

	gettimeofday(&time_stamp, NULL);
	difference = convert_to_miliseconds(subtract_timeval(time_stamp, (*philo)->meal_start_time));
	is_starved = difference > (*philo)->die_time;
	if (is_starved)
	{
		(*info)->is_terminated = true;
		printf("%d %d died\n", difference, (*philo)->philo_nb);
		pthread_mutex_unlock(&(*info)->info_mutex);
		return (1);
	}
	else
	{
		pthread_mutex_lock(*philo_lock);
		(*philo)->meal_start_time.tv_sec = time_stamp.tv_sec;
		(*philo)->meal_start_time.tv_usec = time_stamp.tv_usec;
		pthread_mutex_unlock(*philo_lock);
		pthread_mutex_unlock(&(*info)->info_mutex);
		return (0);
	}
}
