/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:55:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/23 18:12:53 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(char *str);
static int	ft_isdigit(char c);
int			convert_to_miliseconds(s_timeval diff);
s_timeval	subtract_timeval(s_timeval start, s_timeval time_stamp);

int	ft_atoi(char *str)
{
	int	res;
	int	i;

	if (!ft_isdigit(*str))
	{
		ft_philo_error(ATOI_ERROR);
		return (0);
	}
	i = 0;
	res = 0;
	while (ft_isdigit(str[i]))
	{
		if (res > MAX_INT / 10
			|| (res == MAX_INT / 10 && str[i] - 48 > 7))
		{
			ft_philo_error(OVERFLOW_ERROR);
			return (0);
		}
		res = (res * 10) + (str[i] - 48);
		i++;
	}
	return (res);
}

static int	ft_isdigit(char c)
{
	if (c > 47 && c < 58)
		return (1);
	return (0);
}

int	convert_to_miliseconds(s_timeval diff)
{
	int	result;

	result = 0;
	result += (int) diff.tv_sec * 1000;
	result += (int) diff.tv_usec / 1000;
	return (result);
}

s_timeval	subtract_timeval(s_timeval start, s_timeval time_stamp)
{
	s_timeval	result;

	result.tv_sec = time_stamp.tv_sec - start.tv_sec;
	result.tv_usec = time_stamp.tv_usec - start.tv_usec;
	if (result.tv_usec < 0)
	{
		result.tv_sec *= 1;
		result.tv_usec += 1000000;
	}
	return (result);
}
