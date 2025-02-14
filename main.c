/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:59:07 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/14 14:54:44 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc > 4 && argc < 7)
	{
		ft_philo_parse(&data, argv);
		ft_philos_init(&data);
		ft_philo_start(&data);
		//TODO: clean(&data);
	}
	else
		ft_philo_instruct(&data);
	return (0);
}
