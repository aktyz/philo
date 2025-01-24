/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:13:25 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/24 22:00:27 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philo(t_philos **philo)
{
	int			i;
	t_philos	*philos;

	philos = *philo;

	if (philos->philos)
	{
		i = 0;
		while (i < philos->philos[i].info->nb_philos)
		{
			pthread_join(philos->philos[i].philo->thread, NULL);
			pthread_mutex_destroy(&philos->philos[i].philo->philo_lock);
			i++;
		}
		free(philos->philos);
	}
	if (philos->forks)
	{
		i = 0;
		while (i < (*philo)->info->nb_philos)
		{
			pthread_mutex_destroy(&(*philo)->forks[i]);
			i++;
		}
		free(philos->forks);
	}
	if (philos->info)
	{
		pthread_mutex_destroy(&philos->info->info_mutex);
		free(philos->info);
	}
	if (*philo)
		free(*philo);
}
