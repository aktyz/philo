/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:47:10 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/23 20:33:50 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_mutex(t_philo *philo, pthread_mutex_t *forks);

void	init_philo(t_philos ***philos, int argc, char ***argv)
{
	int			i;
	int			j;
	t_philos	*tmp;
	t_philo_r	*r_philo;
	t_waiter_r	*r_waiter;
	s_timeval	time_stamp;
	char		**args;

	(void) argc;
	tmp = **philos;
	args = *argv;
	if (pthread_mutex_init(&tmp->info->info_mutex, NULL))
	{
		ft_philo_error(PTHREAD_INIT_ERROR);
		return ;
	}
	pthread_mutex_lock(&tmp->info->info_mutex);
	tmp->philos = NULL;
	tmp->forks = NULL;
	tmp->waiter = NULL;
	if (args[1])
		tmp->info->nb_philos = ft_atoi(args[1]);
	if (args[2])
		tmp->info->die_time = ft_atoi(args[2]);
	if (args[3])
		tmp->info->eat_time = ft_atoi(args[3]);
	if (args[4])
		tmp->info->sleep_time = ft_atoi(args[4]);
	if (args[5])
	{
		tmp->info->min_eat = ft_atoi(args[5]);
		tmp->info->min_nb_meals = true;
	}
	if ((tmp->info->nb_philos == 0 || tmp->info->die_time == 0
			|| tmp->info->eat_time == 0 || tmp->info->sleep_time == 0)
		|| (tmp->info->min_nb_meals && tmp->info->min_eat == 0))
	{
		ft_philo_error(ZERO_ARG);
		return ;
	}
	if (tmp->info->nb_philos == 1)
	{
		sleep(tmp->info->die_time/1000);
		pthread_mutex_unlock(&tmp->info->info_mutex);
		gettimeofday(&time_stamp, NULL);
		printf("%d %d died\n", convert_to_miliseconds(subtract_timeval(tmp->info->start_time, time_stamp)), 1);
		return ;
	}
	tmp->info->max_think_time = tmp->info->die_time - tmp->info->eat_time;
	tmp->info->max_think_time -= tmp->info->sleep_time;
	tmp->info->is_terminated = false;
	if (tmp->info->max_think_time < 0)
	{
		ft_philo_error(NO_THINK_TIME_AVAILABLE);
		return ;
	}
	tmp->forks = malloc(sizeof(pthread_mutex_t) * tmp->info->nb_philos);
	if (tmp->forks == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	while (i < (tmp->info->nb_philos))
	{
		if (pthread_mutex_init(&tmp->forks[i], NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&tmp->forks[i]);
				j++;
			}
			free(tmp->forks);
			ft_philo_error(PTHREAD_INIT_ERROR);
			return ;
		}
		i++;
	}
	tmp->philos = malloc(sizeof(t_philo) * tmp->info->nb_philos);
	if (tmp->philos == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	r_philo = malloc(sizeof(t_philo_r));
	if (r_philo == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	r_philo->info = tmp->info;
	while (i < (tmp->info->nb_philos))
	{
		tmp->philos[i].philo_status = THINKING;
		tmp->philos[i].philo_nb = i + 1;
		tmp->philos[i].meal_nb = 0;
		tmp->philos[i].meal_start_time.tv_sec = tmp->info->start_time.tv_sec;
		tmp->philos[i].meal_start_time.tv_usec = tmp->info->start_time.tv_usec;
		assign_mutex(&tmp->philos[i], tmp->forks);
		r_philo->philo = &tmp->philos[i];
		if (pthread_create(&tmp->philos[i].thread, NULL, &philo_routine, (void *) r_philo))
		{
			j = 0;
			while (j < i)
			{
				pthread_join(tmp->philos[j].thread, NULL);
				j++;
			}
			free(tmp->philos);
			clean_philo(*philos);
			ft_philo_error(PTHREAD_INIT_ERROR);
		}
		i++;
	}
	r_waiter = malloc(sizeof(t_waiter_r));
	if (r_waiter == NULL)
	{
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	r_waiter->info = tmp->info;
	r_waiter->philos = tmp->philos;
	tmp->waiter = malloc(sizeof(pthread_t *));
	if (pthread_create(tmp->waiter, NULL, &waiter_routine, (void *) r_waiter))
	{
		ft_philo_error(PTHREAD_INIT_ERROR);
		return ;
	}
	pthread_mutex_unlock(&tmp->info->info_mutex);
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
