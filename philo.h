/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:39 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/02 18:58:37 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#ifndef MAX_INT
# define MAX_INT 2147483647
#endif

# include <pthread.h>
# include <time.h>
# include <stdio.h>

/**
 * Program error types
 * 
 */
typedef enum e_philo_errors
{
	ATOI_ERROR,
	MALLOC_ERROR,
	NUM_ERRORS
}	t_philo_errors;

extern const char *philo_error_messages[NUM_ERRORS];

/**
 * Structure to store user arguments
 * 
 */
typedef struct s_args
{
	int	philos;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	min_eat;
}	t_args;

/**
 * Our program structure
 * 
 */
typedef struct s_philo
{
	t_args	*info;
}	t_philo;

/**
 * Program utils
 * 
 */
int	ft_atoi(char *str);

/**
 * Error handling
 */
void	ft_philo_error(t_philo_errors e_nb);

#endif
