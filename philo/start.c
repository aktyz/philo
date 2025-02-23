/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:21 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 20:45:45 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		ft_philo_start(t_data *data);
void		*ft_philo_task(void *data);
static void	ft_one_philo(t_data *data);
static void	ft_philo_eat(t_philo *philo);
static void	ft_philo_think(t_philo *philo);

/**
 * Function starting the actual simulation
 *
 */
void	ft_philo_start(t_data *data)
{
	int	i;

	ft_set_start_time(data);
	if (data->min_eat == 0)
		return ;
	else if (data->nb_philos == 1)
		ft_one_philo(data);
	else
		ft_threads_creation(data);
	while (!ft_is_philo_finished(data))
	{
		i = -1;
		while (++i < data->nb_philos)
		{
			if (ft_is_philo_starved(&data->philos[i]))
			{
				ft_philo_log(DIE, &data->philos[i]);
				break ;
			}
		}
	}
	ft_wait_all_threads(data);
}

/**
 * Function passed to pthread_create(), it contains the loop
 * used by each philosopher to achieve their tasks
 *
 */
void	*ft_philo_task(void *data)
{
	t_philo	*philo;
	long	sleep_time;

	
	philo = (t_philo *)data;
	sleep_time = ft_get_long(&philo->data->data_mutex.lock,
		&philo->data->sleep_time);
	ft_wait_for_all(&philo->data->start_mutex.lock);
	while (!ft_is_philo_finished(philo->data))
	{
		if (philo->full)
			break ;
		if (!ft_is_philo_starved(philo))
			ft_philo_eat(philo);
		if (!ft_is_philo_starved(philo))
			ft_philo_log(SLEEP, philo);
		if (!ft_is_philo_starved(philo))
			ft_usleep(sleep_time, philo, false);
		if (!ft_is_philo_starved(philo))
			ft_philo_think(philo);
	}
	return (NULL);
}

/**
 * Function used by each philo to eat, it has a structure:
 * - pick up forks - one by one
 * - if not starved start eating else die
 * - if not starved and finished eating put down the forks
 * - mechanisms for exiting if the 6th arg passed to main
 *
 */
static void	ft_philo_eat(t_philo *philo)
{
	long	eat_time;

	eat_time = ft_get_long(&philo->data->data_mutex.lock,
		&philo->data->eat_time);
	if (!pthread_mutex_lock(&philo->first_fork->lock))
	{
		ft_philo_log(TAKE_FORK, philo);
		if (pthread_mutex_lock(&philo->second_fork->lock))
			pthread_mutex_unlock(&philo->first_fork->lock);
		else
			ft_philo_log(TAKE_FORK, philo);
	}
	if (!ft_is_philo_starved(philo))
	{
		ft_set_long(&philo->philo_lock.lock, &philo->last_meal_time,
			ft_get_time(MICROSEC, philo->data));
		ft_philo_log(EAT, philo);
		ft_usleep(eat_time, philo, true);
	}
	else
		ft_philo_log(DIE, philo);
	pthread_mutex_unlock(&philo->first_fork->lock);
	pthread_mutex_unlock(&philo->second_fork->lock);
	pthread_mutex_lock(&philo->philo_lock.lock);
	philo->meals_count++;
	if (philo->data->min_eat > 0 && philo->meals_count == philo->data->min_eat)
	{
		philo->full = true;
		ft_inc_long(&philo->data->data_mutex.lock,
			&philo->data->nb_philos_full);
	}
	pthread_mutex_unlock(&philo->philo_lock.lock);
}

/**
 * Function used by each philo to think, which is
 * - announcing it
 * - thinking for a very small amount of time so that hungrier philo can
 * pick up the forks
 *
 */
static void	ft_philo_think(t_philo *philo)
{
	long time;

	time = ft_get_long(&philo->data->data_mutex.lock,
		&philo->data->max_think_time);
	ft_philo_log(THINK, philo);
	ft_usleep(time / 100, philo, false);
}

/**
 * Simple logs in case there's only one philosopher
 * who will never eat because he is missing second fork
 *
 */
static void	ft_one_philo(t_data *data)
{
	ft_philo_log(TAKE_FORK, data->philos);
	ft_philo_log(DIE, data->philos);
}
