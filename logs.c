/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/10 19:31:16 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline void	take_fork(long time, int philo);
static inline void	eating(long time, int philo);
static inline void	sleeping(long time, int philo);
static inline void	thinking(long time, int philo);

void	log_status(t_log status, t_philo *philo)
{
	long	elapsed;

	elapsed = ft_get_time(MILISEC, philo->data) - philo->data->start_time;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->data->log_mutex);
	if (!is_dinner_finished(philo->data))
	{
		switch (status)
		{
			case TAKE_FORK:
				take_fork(elapsed, philo->id);
				break;
			case EAT:
				eating(elapsed, philo->id);
				break;
			case SLEEP:
				sleeping(elapsed, philo->id);
				break;
			case THINK:
				thinking(elapsed, philo->id);
				break;
			default:
				break;
		}
	}
	if (status == DIE)
		printf("%-6ld %d died\n", elapsed, philo->id);
	pthread_mutex_unlock(&philo->data->log_mutex);
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
