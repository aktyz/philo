/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:58:41 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/15 20:04:52 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void				ft_philo_parse(t_data *data, char *argv[]);
static long			ft_philo_atol(const char *str, t_data *data);
static const char	*ft_philo_validate(const char *str, t_data *data);
static inline bool		ft_is_space(char c);
static inline bool		ft_is_digit(char c);

/**
 * Function reading user arguments and saving it in the program main structure
 * User arguments are saved in program memory in MICROSECs
 *
 */
void	ft_philo_parse(t_data *data, char *argv[])
{
	data->nb_philos = ft_philo_atol(argv[1], data);
	data->die_time = ft_philo_atol(argv[2], data) * 1e3;
	data->eat_time = ft_philo_atol(argv[3], data) * 1e3;
	data->sleep_time = ft_philo_atol(argv[4], data) * 1e3;
	if (!data->is_error)
	{
		data->max_think_time = data->die_time - data->eat_time;
		data->max_think_time -= data->sleep_time;
		if (argv[5])
			data->min_eat = ft_philo_atol(argv[5], data);
		else
			data->min_eat = -1;
	}
}

/**
 * Function converting string from user argument to long value
 *
 */
static long	ft_philo_atol(const char *str, t_data *data)
{
	long	result;

	result = 0;
	str = ft_philo_validate(str, data);
	while (ft_is_digit(*str))
	{
		result = (result * 10) + (*str - 48);
		str++;
	}
	if (result > MAX_INT)
		ft_philo_error(ATOI_ERROR, data);
	return (result);
}

/**
 * Function checking input number for:
 * - not being negative
 * - correct number
 * - not overflowing int min or max
 *
 */
static const char	*ft_philo_validate(const char *str, t_data *data)
{
	int			len;
	const char	*result;

	len = 0;
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_philo_error(ATOI_ERROR, data);
	if (!ft_is_digit(*str))
		ft_philo_error(ATOI_ERROR, data);
	result = str;
	while (ft_is_digit(*str++))
		len++;
	if (len > 10)
		ft_philo_error(ATOI_ERROR, data);
	return (result);
}

static inline bool	ft_is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool	ft_is_digit(char c)
{
	return (c > 47 && c < 58);
}
