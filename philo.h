/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 17:33:39 by zslowian          #+#    #+#             */
/*   Updated: 2025/01/23 20:28:15 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

# include <pthread.h>
# include <stdio.h>		//printf
# include <stdlib.h>	//malloc, free
# include <string.h>	//memset
# include <sys/time.h>	//gettimeofday
# include <unistd.h>	//usleep, write
# include <stdbool.h>	//bool

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
	PTHREAD_INIT_ERROR,
	NO_THINK_TIME_AVAILABLE,
	NB_ERRORS
}	t_philo_errors;

typedef enum e_philo_status
{
	EATING,
	SLEEPING,
	THINKING,
	DEAD,
	NB_PHILO_STATUS
}	t_philo_status;

typedef struct timeval s_timeval;
/**
 * Structure to store user arguments
 *
 */
typedef struct s_args
{
	int				nb_philos;
	bool			is_terminated;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	bool			min_nb_meals;
	int				min_eat;
	int				max_think_time;
	s_timeval		start_time;
	pthread_mutex_t	info_mutex;
}	t_args;

typedef struct s_philo
{
	pthread_t			thread;
	int					philo_nb;
	int					meal_nb;
	s_timeval			meal_start_time;
	t_philo_status		philo_status;
	pthread_mutex_t		*first_fork;
	pthread_mutex_t		*second_fork;
}	t_philo;

/**
 * Our program structure
 *
 */
typedef struct s_philos
{
	t_args			*info;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_t		*waiter;
}	t_philos;
/**
 * Core functions
 * 
 */
void	init_philo(t_philos ***philo, int argc, char ***argv);
void	clean_philo(t_philos **philo);

/**
 * Program utils
 *
 */
int			ft_atoi(char *str);
int			convert_to_miliseconds(s_timeval diff);
s_timeval	subtract_timeval(s_timeval start, s_timeval time_stamp);

/**
 * Printing functions
 *
 */
void	take_fork(int milisec, int philo, pthread_mutex_t *lock);
void	eating(int milisec, int philo, pthread_mutex_t *lock);
void	sleeping(int milisec, int philo, pthread_mutex_t *lock);
void	thinking(int milisec, int philo, pthread_mutex_t *lock);

/**
 * Error handling
 *
 */
void	ft_philo_error(t_philo_errors e_nb);

/**
 * Threads routines - philosopher
 *
 */
typedef struct s_philo_r
{
	t_args	*info;
	t_philo	*philo;
}	t_philo_r;

void	*philo_routine(void *param);
void	philo_take_forks(t_philo *philo, t_args *info);
void	philo_eat(t_philo *philo, t_args *info);
void	philo_put_down_forks(t_philo *philo);
void	philo_sleep(t_philo *philo, t_args *info);
void	philo_think(t_philo *philo, t_args *info);

/**
 * Threads routines - waiter
 *
 */
typedef struct s_waiter_r
{
	t_args		*info;
	t_philo		*philos;
}	t_waiter_r;

void	*waiter_routine(void *param);

#endif
