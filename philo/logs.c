/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 11:34:30 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	take_fork(long time, int philo);
static inline void	eating(long time, int philo);
static inline void	sleeping(long time, int philo);
static inline void	thinking(long time, int philo);

/**
 * Function logging necessary messages of philosophers tasks
 *
 */
void	ft_philo_log(t_log status, t_philo *philo)
{
	long		elapsed;
	static bool	is_log_off;

	elapsed = ft_get_time(MILISEC, philo->data) - philo->data->start_time_mili;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->data->log_mutex.lock);
	if (!is_log_off)
	{
		if (status == TAKE_FORK)
			take_fork(elapsed, philo->id);
		else if (status == EAT)
			eating(elapsed, philo->id);
		else if (status == SLEEP)
			sleeping(elapsed, philo->id);
		else if (status == THINK)
			thinking(elapsed, philo->id);
		else if (status == DIE)
		{
			is_log_off = true;
			printf("%-6ld %d died\n", elapsed, philo->id);
		}
	}
	pthread_mutex_unlock(&philo->data->log_mutex.lock);
}

static inline void	take_fork(long time, int philo)
{
	printf("%-6ld %d has taken a fork\n", time, philo);
}

static inline void	eating(long time, int philo)
{
	printf("%-6ld %d is eating\n", time, philo);
}

static inline void	sleeping(long time, int philo)
{
	printf("%-6ld %d is sleeping\n", time, philo);
}

static inline void	thinking(long time, int philo)
{
	printf("%-6ld %d is thinking\n", time, philo);
}
