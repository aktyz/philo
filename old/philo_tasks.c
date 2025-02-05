/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_tasks.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/20 14:41:05 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/24 21:41:27 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_take_forks(t_philo *philo, s_timeval start,
	pthread_mutex_t *lock);
void	philo_eat(t_philo *philo,  s_timeval start, pthread_mutex_t *lock,
	unsigned int eat_time);
void	philo_put_down_forks(t_philo *philo);
void	philo_sleep(t_philo *philo,  s_timeval start, pthread_mutex_t *lock,
	unsigned int sleep_time);
void	philo_think(t_philo *philo,  s_timeval start, pthread_mutex_t *lock,
	unsigned int max_think_time);

void	philo_take_forks(t_philo *philo,  s_timeval start, pthread_mutex_t *lock)
{
	s_timeval	time_stamp;
	int			philo_nb;


	pthread_mutex_lock(&philo->philo_lock);
	pthread_mutex_lock(philo->first_fork);
	philo_nb = philo->philo_nb;
	gettimeofday(&time_stamp, NULL);
	take_fork(convert_to_miliseconds(subtract_timeval(start, time_stamp)), philo_nb, lock); //LOG
	pthread_mutex_lock(philo->second_fork);
	pthread_mutex_unlock(&philo->philo_lock);
	gettimeofday(&time_stamp, NULL);
	take_fork(convert_to_miliseconds(subtract_timeval(start, time_stamp)), philo_nb, lock); //LOG
}

void	philo_eat(t_philo *philo,  s_timeval start, pthread_mutex_t *lock, unsigned int eat_time)
{
	s_timeval	time_stamp;

	philo->philo_status = EATING;
	gettimeofday(&time_stamp, NULL);
	eating(convert_to_miliseconds(subtract_timeval(start, time_stamp)), philo->philo_nb, lock); //LOG
	sleep(eat_time/1000);
}

void	philo_put_down_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->philo_lock);
	pthread_mutex_unlock(philo->first_fork);
	pthread_mutex_unlock(philo->second_fork);
	pthread_mutex_unlock(&philo->philo_lock);
}

void	philo_sleep(t_philo *philo,  s_timeval start, pthread_mutex_t *lock, unsigned int sleep_time)
{
	s_timeval	time_stamp;

	philo->philo_status = SLEEPING;
	gettimeofday(&time_stamp, NULL);
	sleeping(convert_to_miliseconds(subtract_timeval(start, time_stamp)), philo->philo_nb, lock); //LOG
	sleep(sleep_time/1000);
}

void	philo_think(t_philo *philo,  s_timeval start, pthread_mutex_t *lock, unsigned int max_think_time)
{
	s_timeval	time_stamp;

	philo->philo_status = THINKING;
	gettimeofday(&time_stamp, NULL);
	thinking(convert_to_miliseconds(subtract_timeval(start, time_stamp)), philo->philo_nb, lock); //LOG
	sleep((max_think_time/1000)/10);
}
