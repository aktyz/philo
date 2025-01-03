/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:55:30 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/02 18:37:04 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int			ft_atoi(char *str);
static int	ft_isdigit(char c);

int	ft_atoi(char *str)
{
	int	res;
	int	i;
	
	if (!ft_isdigit(*str))
		ft_philo_error(ATOI_ERROR);
	i = 0;
	while (ft_isdigit(str[i]))
	{
		if (res > MAX_INT / 10
			|| (res == MAX_INT / 10 && str[i] - 48 > 7))
			ft_philo_error();
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
