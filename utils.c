/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:51 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/13 21:48:44 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_malloc(size_t bytes, t_data *data);
long	ft_get_time(t_time_code time_code, t_data *data);
void	ft_usleep(long usec, t_data *data);
bool	is_starved(t_philo *philo);

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
	return (-1);
}

/**
 * Precise usleep
 *
 */
void	ft_usleep(long usec, t_data *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = ft_get_time(MICROSEC, data);
	while (ft_get_time(MICROSEC, data) - start < usec)
	{
		if (is_dinner_finished(data))
			break;
		elapsed = ft_get_time(MICROSEC, data) - start;
		remaining = usec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while (ft_get_time(MICROSEC, data) - start < usec)
				;
		}
	}
}
/**
 * Function returning true if philosopher waited too long for
 * his meal and is dying.
 * 
 * Returining false if philo is good to go for another round
 *
 */
bool	is_starved(t_philo *philo)
{
	long	elapsed;

	elapsed = ft_get_time(MICROSEC, philo->data) - philo->last_meal_time;
	if (elapsed >= (philo->data->die_time))
	{
		set_bool(&philo->data->data_mutex, &philo->data->is_anyone_dead, true);
		return (true);
	}
	else
		return (false);
}
