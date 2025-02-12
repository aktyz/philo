/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:21 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/12 18:26:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_task(void *data);
static void	one_philo(t_data *data);
static void	eat(t_philo *philo);
static void	think(t_philo *philo);

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	data->start_time = ft_get_time(MILISEC, data);
	if (data->min_eat == 0)
		return ;
	else if (data->nb_philos == 1)
		one_philo(data);
	else
	{
		while (++i < data->nb_philos)
		{
			pthread_create(&data->philos[i].thread_id, NULL, philo_task,
				&data->philos[i]);
			printf("%d philo thread created\n", i + 1);
			increment_long(&data->data_mutex, &data->nb_threads_ready);
		}
	}
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(data->philos[i].thread_id, NULL);
	
}

static void	*philo_task(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	while (!is_v1_equal_v2(&philo->data->data_mutex, &philo->data->nb_philos, &philo->data->nb_philos_full))
		;
	while (!is_dinner_finished(philo->data)) // shouldn't this be in monitor thread
	{
		if (philo->full)
			break;
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
	philo->last_meal_time = ft_get_time(MILISEC, philo->data);
	philo->meals_count++;
	log_status(EAT, philo);
	ft_usleep(philo->data->eat_time, philo->data);
	if (philo->data->min_eat > 0
			&& philo->meals_count == philo->data->min_eat)
			{
				philo->full = true;
				increment_long(&philo->data->data_mutex,
					&philo->data->nb_philos_full);
			}
	pthread_mutex_unlock(&philo->first_fork->fork);
	pthread_mutex_unlock(&philo->second_fork->fork);
}

static void think(t_philo *philo)
{
	log_status(THINK, philo);
}

static void one_philo(t_data *data)
{
	log_status(TAKE_FORK, data->philos);
	log_status(DIE, data->philos);
}