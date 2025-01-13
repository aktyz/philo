/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 14:08:46 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/13 18:01:10 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(int milisec, int philo)
{
	printf("%d %d has taken a fork\n", milisec, philo);
}

void	eating(int milisec, int philo)
{
	printf("%d %d is eating\n", milisec, philo);
}

void	sleeping(int milisec, int philo)
{
	printf("%d %d is sleeping\n", milisec, philo);
}

void	thinking(int milisec, int philo)
{
	printf("%d %d is thinking\n", milisec, philo);
}

void	die(int milisec, int philo)
{
	printf("%d %d died\n", milisec, philo);
}
