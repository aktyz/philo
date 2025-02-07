/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:51 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/07 16:58:53 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t bytes, t_data *data);
long	ft_get_time(t_time_code time_code, t_data *data);

/**
 * Wrapper around malloc function with a check if malloc
 * succeeded.
 *
 */
void	*ft_malloc(size_t bytes, t_data *data)
{
	void	*result;

	result = malloc(bytes);
	if (result == NULL)
		ft_philo_error(MALLOC_ERROR, data);
	return (result);
}

/**
 * Our chronometer function
 *
 * seconds -> miliseconds -> mi
 */
long	ft_get_time(t_time_code time_code, t_data *data)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		ft_philo_error(TIME_ISSUE, data);
	if (time_code == SEC)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	if (time_code == MILISEC)
		return ((tv.tv_sec * 1e3) + (tv.tv_usec / 1e3));
	if (time_code == MICROSEC)
		return ((tv.tv_sec * 1e6) + (tv.tv_usec));
	ft_philo_error(TIME_ISSUE, data);
	return (NULL);
}
