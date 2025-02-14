/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 15:09:33 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_inc_long(pthread_mutex_t *lock, long *v);
bool	ft_is_philo_starved(t_philo *philo);
void	ft_set_start_time(t_data *data);

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
 * Returining false if philo is good to go for another round
 *
 */
bool	ft_is_philo_starved(t_philo *philo)
{
	long	elapsed;

	elapsed = ft_get_time(MICROSEC, philo->data) - philo->last_meal_time;
	if (elapsed >= (philo->data->die_time))
	{
		ft_set_bool(&philo->data->data_mutex,
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

	start = ft_get_time(MICROSEC, data);
	i = -1;
	data->start_time = start;
	while (++i < data->nb_philos)
		data->philos[i].last_meal_time = start;
}
