/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 20:46:07 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_inc_long(pthread_mutex_t *lock, long *v);
bool		ft_is_philo_starved(t_philo *philo);
void		ft_set_start_time(t_data *data);
bool		ft_mutex_creation(t_data *data);
static bool	ft_create_data_locks(t_data *data);

/**
 * Wrapper around a mutex protected long value
 *
 */
void	ft_inc_long(pthread_mutex_t *lock, long *v)
{
	pthread_mutex_lock(lock);
	*v += 1;
	pthread_mutex_unlock(lock);
}

/**
 * Function returning true if philosopher waited too long for
 * his meal and is dying.
 * 
 * Returining false if philo is good to go for another task
 *
 */
bool	ft_is_philo_starved(t_philo *philo)
{
	long	elapsed;
	long	last_meal_time;
	long	die_time;
	
	last_meal_time = ft_get_long(&philo->philo_lock.lock,
		&philo->last_meal_time);
	die_time = ft_get_long(&philo->data->data_mutex.lock,
		&philo->data->die_time);
	elapsed = ft_get_time(MICROSEC, philo->data) - last_meal_time;
	if (elapsed >= (die_time))
	{
		ft_set_bool(&philo->data->data_mutex.lock,
			&philo->data->is_sym_ended, true);
		return (true);
	}
	else
		return (false);
}

/**
 * Function setting the symulation start time and copying it over
 * to each philosopher as last meal start time
 *
 */
void	ft_set_start_time(t_data *data)
{
	long	start;
	int		i;

	start = ft_get_time(MILISEC, data);
	data->start_time_mili = start;
	data->start_time_micro = start * 1e3;
	i = -1;
	while (++i < data->nb_philos)
		data->philos[i].last_meal_time = data->start_time_micro;
}

/**
 * Function initializing all program locks (mutex)
 * - 3 in main data structure
 * - one for each philosopher
 * Function returns false if any of the mutex creation fails,
 * and true if all went good
 */
bool	ft_mutex_creation(t_data *data)
{
	int	i;
	int	is_success;

	is_success = ft_create_data_locks(data);
	if (!is_success)
		return (false);
	i = -1;
	while (++i < data->nb_philos)
	{
		is_success = pthread_mutex_init(&data->forks[i].lock, NULL);
		if (is_success == 0)
			data->forks[i].lock_id = i;
		else
		{
			ft_destroy_previous_mutexes(data, i);
			ft_philo_error(MUTEX_INIT_ERROR, data);
			return (false);
		}
	}
	return (true);
}

static bool	ft_create_data_locks(t_data *data)
{
	int	i;
	int	is_success;

	i = -1;
	is_success = pthread_mutex_init(&data->data_mutex.lock, NULL);
	if (is_success == 0)
	{
		data->data_mutex.lock_id = 1;
		is_success = pthread_mutex_init(&data->log_mutex.lock, NULL);
		if (is_success == 0)
		{
			data->log_mutex.lock_id = 1;
			is_success = pthread_mutex_init(&data->start_mutex.lock,
					NULL);
			if (is_success == 0)
				data->start_mutex.lock_id = 1;
		}
	}
	if (is_success != 0)
	{
		ft_philo_error(DATA_MUTEX_ERROR, data);
		return (false);
	}
	return (true);
}
