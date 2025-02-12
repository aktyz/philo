/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:31 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/12 18:20:18 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	increment_long(pthread_mutex_t *lock, long *v)
{
	pthread_mutex_lock(lock);
	*v += 1;
	pthread_mutex_unlock(lock);
}

bool	is_v1_equal_v2(pthread_mutex_t *lock, long *v1, long *v2)
{
	long	a;
	long	b;
	pthread_mutex_lock(lock);
	a = *v1;
	b = *v2;
	pthread_mutex_unlock(lock);
	if (a == b)
		return (true);
	return (false);
}
