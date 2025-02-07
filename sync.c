/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/07 17:02:08 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/**
 * SPINLOCK to sync all threads - wait for all threads creation
 *
 */
void	all_threads_ready(t_data *data)
{
	while (!get_bool(&data->data_mutex, &data->are_threads_ready))
		;
}
