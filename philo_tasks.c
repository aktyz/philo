/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:41:05 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 14:41:55 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo, s_timeval start_time);
void	philo_eat(t_philo *philo, int eat_time, s_timeval start_time);
void	philo_put_down_forks(t_philo *philo);
void	philo_sleep(t_philo *philo, int sleep_time, s_timeval start_time);
void	philo_think(t_philo *philo, s_timeval start_time, int max);

void	philo_take_forks(t_philo *philo, s_timeval start_time)
{
	s_timeval	time_stamp;

	pthread_mutex_lock(&philo->first_fork->fork_mutex);
	philo->first_fork->fork_status = TAKEN;
	gettimeofday(&time_stamp, NULL);
	take_fork(convert_to_miliseconds(subtract_timeval(start_time, time_stamp)), philo->philo_nb); //LOG
	pthread_mutex_lock(&philo->second_fork->fork_mutex);
	philo->second_fork->fork_status = TAKEN;
	gettimeofday(&time_stamp, NULL);
	take_fork(convert_to_miliseconds(subtract_timeval(start_time, time_stamp)), philo->philo_nb); //LOG
}

void	philo_eat(t_philo *philo, int eat_time, s_timeval start_time)
{
	s_timeval	time_stamp;

	philo->philo_status = EATING;
	gettimeofday(&time_stamp, NULL);
	eating(convert_to_miliseconds(subtract_timeval(start_time, time_stamp)), philo->philo_nb); //LOG
	sleep(eat_time/1000);
}

void	philo_put_down_forks(t_philo *philo)
{
	pthread_mutex_unlock(&philo->first_fork->fork_mutex);
	philo->first_fork->fork_status = AVAILABLE;
	pthread_mutex_unlock(&philo->second_fork->fork_mutex);
	philo->second_fork->fork_status = AVAILABLE;
}

void	philo_sleep(t_philo *philo, int sleep_time, s_timeval start_time)
{
	s_timeval	time_stamp;

	philo->philo_status = SLEEPING;
	gettimeofday(&time_stamp, NULL);
	sleeping(convert_to_miliseconds(subtract_timeval(start_time, time_stamp)), philo->philo_nb); //LOG
	sleep(sleep_time/1000);
}

void	philo_think(t_philo *philo, s_timeval start_time, int max)
{
	s_timeval	time_stamp;

	philo->philo_status = THINKING;
	gettimeofday(&time_stamp, NULL);
	thinking(convert_to_miliseconds(subtract_timeval(start_time, time_stamp)), philo->philo_nb); //LOG
	sleep((max/1000)/10);
}
