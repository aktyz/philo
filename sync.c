/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/13 21:57:48 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_long(pthread_mutex_t *lock, long *v);
bool	is_v1_equal_v2(pthread_mutex_t *lock, long *v1, long *v2);
void	wait_on_mutex(pthread_mutex_t *lock);
void	create_philo_threads(t_data *data);
void	set_start_time(t_data *data);

void	increment_long(pthread_mutex_t *lock, long *v)
{
	pthread_mutex_lock(lock);
	*v += 1;
	pthread_mutex_unlock(lock);
}

bool	is_v1_equal_v2(pthread_mutex_t *lock, long *v1, long *v2)
{
	long	a;
	long	b;
	pthread_mutex_lock(lock);
	a = *v1;
	b = *v2;
	pthread_mutex_unlock(lock);
	if (a == b)
		return (true);
	return (false);
}

void	wait_on_mutex(pthread_mutex_t *lock)
{
	pthread_mutex_lock(lock);
	pthread_mutex_unlock(lock);
}

void	create_philo_threads(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->start);
	while (++i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, philo_task,
			&data->philos[i]);
		increment_long(&data->data_mutex, &data->nb_threads_ready);
	}
	pthread_mutex_unlock(&data->start);
}

void	set_start_time(t_data *data)
{
	long	start;
	int		i;

	start = ft_get_time(MICROSEC, data);
	i = -1;
	data->start_time = start;
	while (++i < data->nb_philos)
		data->philos[i].last_meal_time = start;
}
