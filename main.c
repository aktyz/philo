/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:54 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/14 19:51:25 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_philo(t_philos **philo, int argc, char ***argv);
static void	init_philo(t_philos ***philo, int argc, char ***argv);
static void	clean_philo(t_philos **philo);
static void	how_to_run(void);

int	main(int argc, char **argv)
{
	t_philos	*philo;

	if (argc == 5 || argc == 6)
	{
		philo = malloc(sizeof(t_philos));
		if (philo == NULL)
			ft_philo_error(MALLOC_ERROR);
		launch_philo(&philo, argc, &argv);
		clean_philo(&philo);
	}
	else
	{
		how_to_run();
		return (1);
	}
	return (0);
}

static void	launch_philo(t_philos **philo, int argc, char ***argv)
{
	(*philo)->min_nb_meals = 0;
	(*philo)->info = malloc(sizeof(t_args));
	if ((*philo)->info == NULL)
	{
		clean_philo(philo);
		ft_philo_error(MALLOC_ERROR);
	}
	init_philo(&philo, argc, argv);
	// TODO: start the symulation
}

static void	init_philo(t_philos ***philo, int argc, char ***argv)
{
	int			i;
	t_philos	*tmp;
	char		**args;
	//t_philo		*tmp_philo;
	//t_cutlery	*tmp_fork;

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
	// TODO: create the threads and mutexes in the right structure
	tmp->philos = malloc(sizeof(t_philo) * tmp->info->nb_philos);
	if (tmp->philos == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
	}
	i = 0;
	while (i < (tmp->info->nb_philos))
	{
		pthread_create(&(((tmp->philos) + i)->thread), NULL, &philo_routine, NULL);
		i++;
	}
	tmp->forks = malloc(sizeof(t_cutlery) * tmp->info->nb_philos);
	if (tmp->forks == NULL)
	{
		clean_philo(*philo);
		ft_philo_error(MALLOC_ERROR);
	}
}

static void	clean_philo(t_philos **philo)
{
	int	i;
	
	if ((*philo)->info)
		free((*philo)->info);
	if ((*philo)->philos)
	{
		// TODO: iterate through philos and wait for threads
		i = 0;
		while(i < (*philo)->info->nb_philos)
		{
			pthread_join(((*philo)->philos + i)->thread, NULL);
			i++;
		}
		free((*philo)->philos);
	}
	if ((*philo)->forks)
	{
		// TODO: destroy the mutexes in a loop
		free((*philo)->forks);
	}
	if (*philo)
		free(*philo);
}

static void	how_to_run(void)
{
	printf("Incorrect number of arguments!\n");
	printf("Provide four or five arguments:\n");
	printf("nb_of_philosophers\ttime_to_die\ttime_to_eat\ttime_to_sleep\n");
	printf("\nOptional fifth argument:\n");
	printf("nb_of_times_each_philosopher_must_eat\n");
	ft_philo_error(INCORRECT_NB_ARGS);
}
