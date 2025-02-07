/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:59:18 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/07 17:03:28 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h> //bool
# include <stdio.h> //printf
# include <stdlib.h> //malloc, free
# include <string.h> //memset
# include <sys/time.h> //gettimeofday
# include <unistd.h> //usleep, write

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

typedef struct s_data	t_data;

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
	TIME_ISSUE,
	NB_ERRORS
}						t_philo_errors;

/**
 * Time quantities
 *
 */
typedef enum e_time_code
{
	SEC,
	MILISEC,
	MICROSEC
}						t_time_code;

/**
 * My structure to keep a fork
 *
 */
typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					fork_id;
}						t_fork;

/**
 * Single philo structure
 *
 */
typedef struct s_philo
{
	int			id;
	long		meals_count;
	bool		full;
	long		last_meal_time; // time passed from last meal
	t_fork		*first_fork;
	t_fork		*second_fork;
	t_data		*data;
	pthread_t	thread_id;
}						t_philo;

/**
 * Program main structure
 *
 */
struct					s_data
{
	long			nb_philos;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			min_eat;
	long			start_time;
	bool			is_end;
	bool			are_threads_ready;
	pthread_mutex_t	data_mutex;
	t_fork			*forks;
	t_philo			*philos;
};

/**
 * Program functions
 *
 */
void					parse_input(t_data *data, char *argv[]);
void					data_init(t_data *data);
void					dinner_start(t_data *data);

/**
 * Error management functions
 *
 */
void					ft_philo_error(t_philo_errors e_nb, t_data *data);
void					how_to_run(t_data *data);

/**
 * Utils functions
 *
 */
void					*ft_malloc(size_t bytes, t_data *data);
long					ft_get_time(t_time_code time_code, t_data *data);

/**
 * Thread synchronisations and helpers
 *
 */
void					set_bool(pthread_mutex_t *lock, bool *v, bool new_v);
bool					get_bool(pthread_mutex_t *lock, bool *v);
void					set_long(pthread_mutex_t *lock, long *v, long new_v);
long					get_long(pthread_mutex_t *lock, long *v);
bool					is_dinner_finished(t_data *data);
void					all_threads_ready(t_data *data);

#endif
