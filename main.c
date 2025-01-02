/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:54 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/02 18:36:41 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	launch_philo(int argc, char ***argv);

int	main(int argc, char **argv)
{
	if (argc == 5 || argc == 6)
		launch_philo(argc, &argv);
	else
	{
		printf("Incorrect number of arguments!\n");
		printf("Provide four or five arguments:\n");
		printf("number_of_philosophers time_to_die time_to_eat time_to_sleep\n");
		printf("\nOptional fifth argument:\n");
		printf("number_of_times_each_philosopher_must_eat\n");
		exit(1);
	}	
	return (0);
}

void	launch_philo(int argc, char ***argv)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (philo == NULL)
		ft_philo_error(MALLOC_ERROR);
	init_philo(&philo, argc, argv);
}

void	init_philo(t_philo **philo, int argc, char ***argv)
{
	t_args	*tmp;
	char	**args;
	
	
	tmp = (*philo)->info;
	args = *argv;
	if (args[1])
		tmp->philos = ft_atoi(args[1]);
	if (args[2])
		tmp->die_time = ft_atoi(args[2]);
	if (args[3])
		tmp->eat_time = ft_atoi(args[3]);
	if (args[4])
		tmp->sleep_time = ft_atoi(args[4]);
	if (args[5])
		tmp->min_eat = ft_atoi(args[5]);	
}