/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:21 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/07 17:01:28 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*philo_task(void *data);
static void	one_philo(t_data *data);

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->min_eat == 0)
		return ;
	else if (data->nb_philos == 1)
		one_philo(data);
	else
	{
		while (++i < data->nb_philos)
			pthread_create(&data->philos[i].thread_id, philo_task,
				&data->philos[i], NULL);
	}
	data->start_time = ft_get_time(MILISEC, data);
	set_bool(&data->data_mutex, data->are_threads_ready, true);
	i = -1;
	while (++i < data->nb_philos)
		pthread_join(&data->philos[i].thread_id, NULL);
}

static void	*philo_task(void *data)
{
	t_philo	*philo;

	philo = (t_philo *)data;
	all_threads_ready(philo->data);
	// TODO
}

static void	one_philo(t_data *data)
{
	// TODO
}
