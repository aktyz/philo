/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:59:07 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/10 19:31:44 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc > 4 && argc < 7)
	{
		parse_input(&data, argv);
		data_init(&data);
		dinner_start(&data);
		//clean(&data);
	}
	else
		how_to_run(&data);
	return (0);
}
