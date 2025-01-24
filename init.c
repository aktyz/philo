/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:47:10 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/24 22:22:22 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_mutex(t_philo *philo, pthread_mutex_t *forks);

void	init_philo(t_philos ***philos, char ***argv)
{
	int			i;
	int			j;
	t_philos	*data;
	s_timeval	time_stamp;
	char		**args;

	data = **philos;
	args = *argv;
	// INFO ALLOCATION
	if (pthread_mutex_init(&data->info->info_mutex, NULL))
	{
		ft_philo_error(PTHREAD_INIT_ERROR);
		return ;
	}
	pthread_mutex_lock(&data->info->info_mutex);
	data->philos = NULL;
	data->forks = NULL;
	if (args[1])
		data->info->nb_philos = ft_atoi(args[1]);
	if (args[2])
		data->info->die_time = ft_atoi(args[2]);
	if (args[3])
		data->info->eat_time = ft_atoi(args[3]);
	if (args[4])
		data->info->sleep_time = ft_atoi(args[4]);
	if (args[5])
	{
		data->info->min_eat = ft_atoi(args[5]);
		data->info->min_nb_meals = true;
	}
	if ((data->info->nb_philos == 0 || data->info->die_time == 0
			|| data->info->eat_time == 0 || data->info->sleep_time == 0)
		|| (data->info->min_nb_meals && data->info->min_eat == 0))
	{
		ft_philo_error(ZERO_ARG);
		return ;
	}
	if (data->info->nb_philos == 1)
	{
		sleep(data->info->die_time/1000);
		pthread_mutex_unlock(&data->info->info_mutex);
		gettimeofday(&time_stamp, NULL);
		printf("%d %d died\n", convert_to_miliseconds(subtract_timeval(data->info->program_start_time, time_stamp)), 1);
		return ;
	}
	data->info->max_think_time = data->info->die_time - data->info->eat_time;
	data->info->max_think_time -= data->info->sleep_time;
	data->info->is_terminated = false;
	if (data->info->max_think_time < 0)
	{
		ft_philo_error(NO_THINK_TIME_AVAILABLE);
		return ;
	}
	// FORKS ALLOCATION
	data->forks = malloc(sizeof(pthread_mutex_t) * data->info->nb_philos);
	if (data->forks == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	while (i < (data->info->nb_philos))
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->forks[j]);
				j++;
			}
			free(data->forks);
			ft_philo_error(PTHREAD_INIT_ERROR);
			return ;
		}
		i++;
	}
	// PHILOSOPHERS ALLOCATION
	data->philos = malloc(sizeof(t_philo_r) * data->info->nb_philos);
	if (data->philos == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	while (i < (data->info->nb_philos))
	{
		if (pthread_mutex_init(&data->philos[i].philo_lock, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&data->philos[j].philo_lock);
				j++;
			}
			free(data->philos);
			ft_philo_error(PTHREAD_INIT_ERROR);
			return ;
		}
		i++;
	}
	i = 0;
	while (i < (data->info->nb_philos))
	{
		pthread_mutex_lock(&data->philos[i].philo_lock);
		data->philos[i].info = data->info;
		data->philos[i].philo = malloc(sizeof(t_philo));
		if (data->philos[i].philo == NULL)
		{
			j = 0;
			while (j < i)
			{
				free(data->philos[j].philo);
				j++;
			}
			ft_philo_error(MALLOC_ERROR);
			return ;
		}
		data->philos[i].philo->philo_status = THINKING;
		data->philos[i].philo->philo_nb = i + 1;
		data->philos[i].philo->meal_nb = 0;
		data->philos[i].philo->meal_start_time.tv_sec = data->info->program_start_time.tv_sec;
		data->philos[i].philo->meal_start_time.tv_usec = data->info->program_start_time.tv_usec;
		data->philos[i].philo->die_time = data->info->die_time;
		data->philos[i].philo->eat_time = data->info->eat_time;
		data->philos[i].philo->sleep_time = data->info->sleep_time;
		data->philos[i].philo->max_think_time = data->info->max_think_time;
		assign_mutex(data->philos[i].philo, data->forks);
		if (pthread_create(&data->philos[i].philo->thread, NULL, &philo_routine, (void *) &data->philos[i]))
		{
			j = 0;
			while (j < i)
			{
				pthread_join(data->philos[j].philo->thread, NULL);
				j++;
			}
			free(data->philos);
			clean_philo(*philos);
			ft_philo_error(PTHREAD_INIT_ERROR);
		}
		pthread_mutex_unlock(&data->philos[i].philo_lock);
		i++;
	}
	pthread_mutex_unlock(&data->info->info_mutex);
}

static void	assign_mutex(t_philo *philo, pthread_mutex_t *forks)
{
	if (philo->philo_nb == 1) // philo[0]
	{
		philo->first_fork = &forks[0]; //-> 0
		philo->second_fork = &forks[1]; //-> 1
	}
	else if (philo->philo_nb % 2 == 0) // philo[1, 3, ...]
	{
		philo->first_fork = &forks[0]; // -> 0
		philo->second_fork = &forks[1]; // -> 1
	}
}
