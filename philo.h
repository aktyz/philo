/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:39 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/14 19:53:36 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

# include <pthread.h>
# include <stdio.h>    //printf
# include <stdlib.h>   //malloc, free
# include <string.h>   //memset
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //usleep, write

/**
 * Program error types
 *
 */
typedef enum e_philo_errors
{
	ATOI_ERROR,
	MALLOC_ERROR,
	OVERFLOW_ERROR,
	INCORRECT_NB_ARGS,
	ZERO_ARG,
	NB_ERRORS
}	t_philo_errors;

typedef enum e_cutlery_status
{
	TAKEN,
	NB_STATUS
}	t_cutlery_status;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	NB_PHILO_STATUS
}	t_philo_status;
/**
 * Structure to store user arguments
 *
 */
typedef struct s_args
{
	int	nb_philos;
	int	die_time;
	int	eat_time;
	int	sleep_time;
	int	min_eat;
}	t_args;

typedef struct s_cutlery
{
	t_cutlery_status	fork_status;
	pthread_mutex_t		fork_mutex;
}	t_cutlery;

typedef struct s_philo
{
	pthread_t		thread;
	t_philo_status	philo_status;
	t_cutlery		*left_fork;
	t_cutlery		*right_fork;
}	t_philo;

/**
 * Our program structure
 *
 */
typedef struct s_philos
{
	t_args		*info;
	t_philo		*philos;
	t_cutlery	*forks;
	int			min_nb_meals;
}	t_philos;

/**
 * Program utils
 *
 */
int		ft_atoi(char *str);

/**
 * Printing functions
 *
 */
void	take_fork(int milisec, int philo);
void	eating(int milisec, int philo);
void	sleeping(int milisec, int philo);
void	thinking(int milisec, int philo);
void	die(int milisec, int philo);

/**
 * Error handling
 *
 */
void	ft_philo_error(t_philo_errors e_nb);

/**
 * Threads routines
 *
 */
void	*philo_routine(void *param);

#endif
