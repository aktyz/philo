/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:58 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 16:34:11 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_philos_init(t_data *data);
static void	ft_philo_init(t_data *data);
static void	ft_assign_forks(t_philo *philo, t_fork *forks, int i);
void		ft_threads_creation(t_data *data);

/**
 * Function initializing program main structure
 * and fork mutexes - one per each philosopher
 *
 */
void	ft_philos_init(t_data *data)
{
	int	i;

	i = -1;
	data->is_sym_ended = false;
	data->philos = ft_malloc(data->nb_philos * sizeof(t_philo), data);
	data->forks = ft_malloc(data->nb_philos * sizeof(t_fork), data);
	if (data->philos == NULL || data->forks == NULL)
	{
		ft_philo_error(MALLOC_ERROR, data);
		return ;
	}
	data->nb_philos_full = 0;
	pthread_mutex_init(&data->data_mutex, NULL);
	pthread_mutex_init(&data->log_mutex, NULL);
	pthread_mutex_init(&data->start, NULL);
	while (++i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].fork_id = i;
	}
	ft_philo_init(data);
}

/**
 * Function initializing individual philosopers data
 *
 */
static void	ft_philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nb_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->data = data;
		ft_assign_forks(philo, data->forks, i);
	}
}

/**
 * Function assigning forks to each philosoper - 
 *
 */
static void	ft_assign_forks(t_philo *philo, t_fork *forks, int pos)
{
	int	philo_nb;

	philo_nb = philo->data->nb_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nb];
	}
	else
	{
		philo->first_fork = &forks[(pos + 1) % philo_nb];
		philo->second_fork = &forks[pos];
	}
}

/**
 * Function initializing one thread per philosopher
 *
 */
void	ft_threads_creation(t_data *data)
{
	int	i;

	i = -1;
	pthread_mutex_lock(&data->start);
	while (++i < data->nb_philos)
	{
		pthread_create(&data->philos[i].thread_id, NULL, ft_philo_task,
			&data->philos[i]);
	}
	pthread_mutex_unlock(&data->start);
}
