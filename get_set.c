/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:09 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 11:32:57 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_set_bool(pthread_mutex_t *lock, bool *v, bool new_v);
bool	ft_get_bool(pthread_mutex_t *lock, bool *v);
void	ft_set_long(pthread_mutex_t *lock, long *v, long new_v);
long	ft_get_long(pthread_mutex_t *lock, long *v);
bool	ft_is_philo_finished(t_data *data);

/**
 * Wrapper around updating a bool value protected by it's lock
 *
 */
void	ft_set_bool(pthread_mutex_t *lock, bool *v, bool new_v)
{
	pthread_mutex_lock(lock);
	*v = new_v;
	pthread_mutex_unlock(lock);
}

/**
 * Wrapper around reading a bool value protected by it's lock
 *
 */
bool	ft_get_bool(pthread_mutex_t *lock, bool *v)
{
	bool	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

/**
 * Wrapper around updating a long value protected by it's lock
 *
 */
void	ft_set_long(pthread_mutex_t *lock, long *v, long new_v)
{
	pthread_mutex_lock(lock);
	*v = new_v;
	pthread_mutex_unlock(lock);
}

/**
 * Wrapper around reading a long value protected by it's lock
 *
 */
long	ft_get_long(pthread_mutex_t *lock, long *v)
{
	long	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

/**
 * Wrapper around reading the most imporant bool of the program - should
 * it finish working because one of the philosophers died or because
 * all of the philosophers are full (ate the expected number of meals)
 *
 */
bool	ft_is_philo_finished(t_data *data)
{
	bool	is_starved;
	bool	are_all_full;

	pthread_mutex_lock(&data->data_mutex.lock);
	is_starved = data->is_sym_ended;
	if (data->nb_philos == data->nb_philos_full)
		are_all_full = true;
	else
		are_all_full = false;
	pthread_mutex_unlock(&data->data_mutex.lock);
	return (is_starved || are_all_full);
}
