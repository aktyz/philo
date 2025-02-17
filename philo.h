/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zslowian <zslowian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:59:18 by zslowian          #+#    #+#             */
/*   Updated: 2025/02/17 11:41:28 by zslowian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdbool.h>  //bool
# include <stdio.h>    //printf
# include <stdlib.h>   //malloc, free
# include <string.h>   //memset
# include <sys/time.h> //gettimeofday
# include <unistd.h>   //usleep, write

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
	NO_ERROR,
	ATOI_ERROR,
	OVERFLOW_ERROR,
	MALLOC_ERROR,
	DATA_MUTEX_ERROR,
	MUTEX_INIT_ERROR,
	TIME_ISSUE,
	THRED_INIT_ERROR,
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

typedef enum e_log
{
	TAKE_FORK,
	EAT,
	SLEEP,
	THINK,
	DIE
}						t_log;

/**
 * My structure to keep a fork
 *
 */
typedef struct s_mutex
{
	pthread_mutex_t		lock;
	int					lock_id;
}						t_mutex;

/**
 * Single philo structure
 *
 */
typedef struct s_philo
{
	int					id;
	long				meals_count;
	bool				full;
	long				last_meal_time;
	t_mutex				*first_fork;
	t_mutex				*second_fork;
	t_data				*data;
	pthread_t			thread_id;
}						t_philo;

/**
 * Program main structure
 *
 */
struct					s_data
{
	long				nb_philos;
	long				die_time;
	long				eat_time;
	long				sleep_time;
	long				max_think_time;
	long				min_eat;
	long				nb_philos_full;
	long				start_time_micro;
	long				start_time_mili;
	bool				is_sym_ended;
	t_mutex				data_mutex;
	t_mutex				log_mutex;
	t_mutex				start_mutex;
	t_mutex				*forks;
	t_philo				*philos;
	t_philo_errors		is_error;
};

/**
 * Program functions
 *
 */
void					ft_philo_parse(t_data *data, char *argv[]);
void					ft_philos_init(t_data *data);
void					ft_philo_start(t_data *data);
void					ft_philo_log(t_log status, t_philo *philo);
void					*ft_philo_task(void *data);
void					ft_philo_clean(t_data *data);

/**
 * Error management functions
 *
 */
void					ft_philo_error(t_philo_errors e_nb, t_data *data);
void					ft_philo_instruct(void);

/**
 * Utils functions
 *
 */
void					*ft_malloc(size_t bytes, t_data *data);
long					ft_get_time(t_time_code time_code, t_data *data);
void					ft_usleep(long usec, t_philo *philo, bool is_eating);
void					ft_set_bool(pthread_mutex_t *lock, bool *v, bool new_v);
bool					ft_get_bool(pthread_mutex_t *lock, bool *v);
void					ft_set_long(pthread_mutex_t *lock, long *v, long new_v);
long					ft_get_long(pthread_mutex_t *lock, long *v);
void					ft_inc_long(pthread_mutex_t *lock, long *v);

/**
 * Thread synchronisations and helpers
 *
 */
bool					ft_mutex_creation(t_data *data);
void					ft_destroy_previous_mutexes(t_data *data, int failed);
void					ft_wait_previous_threads(t_data *data, int failed);
void					ft_threads_creation(t_data *data);
void					ft_set_start_time(t_data *data);
void					ft_wait_for_all(pthread_mutex_t *lock);
bool					ft_is_philo_starved(t_philo *philo);
bool					ft_is_philo_finished(t_data *data);

#endif
