/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 17:00:09 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/13 19:34:27 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_bool(pthread_mutex_t *lock, bool *v, bool new_v);
bool	get_bool(pthread_mutex_t *lock, bool *v);
void	set_long(pthread_mutex_t *lock, long *v, long new_v);
long	get_long(pthread_mutex_t *lock, long *v);
bool	is_dinner_finished(t_data *data);

void	set_bool(pthread_mutex_t *lock, bool *v, bool new_v)
{
	pthread_mutex_lock(lock);
	*v = new_v;
	pthread_mutex_unlock(lock);
}

bool	get_bool(pthread_mutex_t *lock, bool *v)
{
	bool	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

void	set_long(pthread_mutex_t *lock, long *v, long new_v)
{
	pthread_mutex_lock(lock);
	*v = new_v;
	pthread_mutex_unlock(lock);
}

long	get_long(pthread_mutex_t *lock, long *v)
{
	long	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

bool	is_dinner_finished(t_data *data) // shouldn't it be in monitor instead
{
	return (get_bool(&data->data_mutex, &data->is_anyone_dead));
}
