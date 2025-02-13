/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:21 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/13 21:47:37 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void		dinner_start(t_data *data);
void		*philo_task(void *data);
static void	one_philo(t_data *data);
static void	eat(t_philo *philo);
static void	think(t_philo *philo);

void	dinner_start(t_data *data)
{
	int	i;

	set_start_time(data);
	if (data->min_eat == 0)
		return ;
	else if (data->nb_philos == 1)
		one_philo(data);
	else
		create_philo_threads(data);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread_id, NULL);
}

void	*philo_task(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	wait_on_mutex(&philo->data->start);
	while (!is_dinner_finished(philo->data))
	{
		if (philo->full)
			break ;
		eat(philo);
		log_status(SLEEP, philo);
		ft_usleep(philo->data->sleep_time, philo->data);
		think(philo);
	}
	return (NULL);
}

static void	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork);
	log_status(TAKE_FORK, philo);
	pthread_mutex_lock(&philo->second_fork->fork);
	log_status(TAKE_FORK, philo);
	if (!is_starved(philo))
	{
		philo->last_meal_time = ft_get_time(MICROSEC, philo->data);
		log_status(EAT, philo);
		ft_usleep(philo->data->eat_time, philo->data);
	}
	else
		log_status(DIE, philo);
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
	philo->meals_count++;
	if (philo->data->min_eat > 0 && philo->meals_count == philo->data->min_eat)
	{
		philo->full = true;
		increment_long(&philo->data->data_mutex, &philo->data->nb_philos_full);
	}
}

static void	think(t_philo *philo)
{
	log_status(THINK, philo);
}

static void	one_philo(t_data *data)
{
	log_status(TAKE_FORK, data->philos);
	log_status(DIE, data->philos);
}
