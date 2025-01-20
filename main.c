/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:54 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/20 14:36:38 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	launch_philo(t_philos **philo, int argc, char ***argv);
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
	gettimeofday(&(*philo)->info->start_time, NULL);
	init_philo(&philo, argc, argv);
	if ((*philo)->forks[(*philo)->info->nb_philos - 1].mutex_init)
	{
		printf("Start the dinner\n");
	}
	clean_philo(philo);
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
