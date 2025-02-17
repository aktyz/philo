/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:13:45 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 12:30:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_philo_clean(t_data *data);
static void	ft_destroy_mutex(t_mutex *lock);
void		ft_destroy_previous_mutexes(t_data *data, int failed);
void		ft_wait_previous_threads(t_data *data, int failed);
void		ft_wait_all_threads(t_data *data);

void	ft_philo_clean(t_data *data)
{
	int	i;

	if (data->is_error == NO_ERROR || data->is_error > 3)
	{
		ft_destroy_mutex(&data->data_mutex);
		ft_destroy_mutex(&data->log_mutex);
		ft_destroy_mutex(&data->start_mutex);
		if (data->is_error == NO_ERROR || data->is_error > 5)
		{
			i = -1;
			while (++i < data->nb_philos)
				ft_destroy_mutex(&data->forks[i]);
		}
		if (data->philos)
			free(data->philos);
		if (data->forks)
			free(data->forks);
	}
}

static void	ft_destroy_mutex(t_mutex *lock)
{
	if (lock->lock_id != 0)
		pthread_mutex_destroy(&lock->lock);
}

void	ft_destroy_previous_mutexes(t_data *data, int failed)
{
	int	i;

	i = -1;
	while (++i < failed)
		ft_destroy_mutex(&data->forks[i]);
}

void	ft_wait_previous_threads(t_data *data, int failed)
{
	int	i;

	i = -1;
	while (++i < failed)
		pthread_join(data->philos[i].thread_id, NULL);
}

void	ft_wait_all_threads(t_data *data)
{
	int	i;

	if (!data->is_error && data->nb_philos > 1)
	{
		i = -1;
		while (++i < data->nb_philos)
			pthread_join(data->philos[i].thread_id, NULL);
	}
}
