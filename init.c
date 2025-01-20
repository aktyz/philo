/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/19 13:47:10 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 15:35:35 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	assign_mutex(int nb, t_philo *philo, t_cutlery *forks);

void	init_philo(t_philos ***philo, int argc, char ***argv)
{
	int			i;
	int			j;
	t_philos	*tmp;
	t_philo_r	*r_args;
	char		**args;

	(void) argc;
	tmp = **philo;
	args = *argv;
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
		tmp->min_nb_meals = 1;
	}
	if ((tmp->info->nb_philos == 0 || tmp->info->die_time == 0
			|| tmp->info->eat_time == 0 || tmp->info->sleep_time == 0)
		|| (tmp->min_nb_meals && tmp->info->min_eat == 0))
	{
		ft_philo_error(ZERO_ARG);
		return ;
	}
	tmp->info->max_think_time = tmp->info->die_time - tmp->info->eat_time;
	tmp->info->max_think_time -= tmp->info->sleep_time;
	if (tmp->info->max_think_time < 0)
	{
		clean_philo(*philo);
		ft_philo_error(NO_THINK_TIME_AVAILABLE);
		return ;
	}
	if (pthread_mutex_init(&tmp->info->print, NULL))
	{
		clean_philo(*philo);
		ft_philo_error(PTHREAD_INIT_ERROR);
		return ;
	}
	tmp->waiter = malloc(sizeof(t_waiter));
	if (tmp->waiter == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	if (pthread_create(&tmp->waiter->waiter, NULL, &waiter_routine, NULL) ||
		pthread_mutex_init(&tmp->waiter->waiter_mutex, NULL))
	{
		clean_philo(*philo);
		ft_philo_error(PTHREAD_INIT_ERROR);
		return ;
	}
	tmp->forks = malloc(sizeof(t_cutlery) * tmp->info->nb_philos);
	if (tmp->forks == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	while (i < (tmp->info->nb_philos))
	{
		(tmp->forks)[i].fork_status = AVAILABLE;
		tmp->forks[i].mutex_init = 0;
		if (pthread_mutex_init(&tmp->forks[i].fork_mutex, NULL) != 0)
		{
			j = 0;
			while (j < i)
			{
				pthread_mutex_destroy(&tmp->forks[i].fork_mutex);
				j++;
			}
			free(tmp->forks);
			clean_philo(*philo);
			ft_philo_error(PTHREAD_INIT_ERROR);
			return ;
		}
		tmp->forks[i].mutex_init = 1;
		i++;
	}
	tmp->philos = malloc(sizeof(t_philo) * tmp->info->nb_philos);
	if (tmp->philos == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	i = 0;
	r_args = malloc(sizeof(t_philo_r));
	if (r_args == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
		return ;
	}
	r_args->info = tmp->info;
	while (i < (tmp->info->nb_philos))
	{
		tmp->philos[i].philo_status = THINKING;
		tmp->philos[i].philo_nb = i + 1;
		tmp->philos[i].meal_nb = 0;
		assign_mutex(tmp->info->nb_philos, &tmp->philos[i], tmp->forks);
		r_args->philo = &tmp->philos[i];
		if (pthread_create(&tmp->philos[i].thread, NULL, &philo_routine, (void *) r_args))
		{
			j = 0;
			while (j < i)
			{
				pthread_join(tmp->philos[j].thread, NULL);
				j++;
			}
			free(tmp->philos);
			clean_philo(*philo);
			ft_philo_error(PTHREAD_INIT_ERROR);
		}
		i++;
	}	
}

static void	assign_mutex(int nb, t_philo *philo, t_cutlery *forks)
{
	int	philo_i;

	philo_i = philo->philo_nb - 1;
	if (philo_i == 0)
	{
		philo->first_fork = &forks[0];
		philo->second_fork = &forks[nb - 1];
	}
	else if (philo_i % 2 != 0)
	{
		philo->first_fork = &forks[philo_i - 1];
		philo->second_fork = &forks[philo_i];
	}
	else if (philo_i % 2 == 0)
	{
		philo->first_fork = &forks[philo_i];
		philo->second_fork = &forks[philo_i - 1];
	}
}
