/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 15:13:25 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/19 15:13:49 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_philo(t_philos **philo)
{
	int	i;

	if ((*philo)->philos)
	{
		i = 0;
		while (i < (*philo)->info->nb_philos)
		{
			pthread_join((*philo)->philos[i].thread, NULL);
			i++;
		}
		free((*philo)->philos);
	}
	if ((*philo)->forks)
	{
		i = 0;
		while (i < (*philo)->info->nb_philos)
		{
			pthread_mutex_destroy(&(*philo)->forks[i].fork_mutex);
			i++;
		}
		free((*philo)->forks);
	}
	if ((*philo)->info)
		free((*philo)->info);
	if (*philo)
		free(*philo);
}
