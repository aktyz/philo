/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:59:07 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/15 19:45:28 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	data.is_error = NO_ERROR;
	if (argc > 4 && argc < 7)
	{
		ft_philo_parse(&data, argv);
		ft_philos_init(&data);
		ft_philo_start(&data);
		ft_philo_clean(&data);
	}
	else if (data.is_error == NO_ERROR)
		ft_philo_instruct();
	return (0);
}
