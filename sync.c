/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/12 14:17:30 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_long(pthread_mutex_t *lock, long *v)
{
	pthread_mutex_lock(lock);
	*v += 1;
	pthread_mutex_unlock(lock);
}

bool	compare_long(t_data *data, long *v1, long *v2)
{
	bool res;

	pthread_mutex_lock(&data->data_mutex);
	res = (*v1 == *v2);
	pthread_mutex_unlock(&data->data_mutex);
	return (res);
}
