/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 15:49:07 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(int milisec, int philo, pthread_mutex_t *lock);
void	eating(int milisec, int philo, pthread_mutex_t *lock);
void	sleeping(int milisec, int philo, pthread_mutex_t *lock);
void	thinking(int milisec, int philo, pthread_mutex_t *lock);
void	die(int milisec, int philo, pthread_mutex_t *lock);

void	take_fork(int milisec, int philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d has taken a fork\n", milisec, philo);
	pthread_mutex_unlock(lock);
}

void	eating(int milisec, int philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d is eating\n", milisec, philo);
	pthread_mutex_unlock(lock);
}

void	sleeping(int milisec, int philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d is sleeping\n", milisec, philo);
	pthread_mutex_unlock(lock);
}

void	thinking(int milisec, int philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d is thinking\n", milisec, philo);
	pthread_mutex_unlock(lock);
}

void	die(int milisec, int philo, pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	printf("%d %d died\n", milisec, philo);
	pthread_mutex_unlock(lock);
}
