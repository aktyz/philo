/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 16:13:45 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 16:35:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_philo_clean(t_data *data);

void	ft_philo_clean(t_data *data)
{
	int	i;

	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->log_mutex);
	pthread_mutex_destroy(&data->start);
	i = -1;
	while (++i < data->nb_philos)
	{
		pthread_mutex_destroy(&data->forks[i].fork);
	}
	if (data->philos)
		free(data->philos);
	if (data->forks)
		free(data->forks);
}
