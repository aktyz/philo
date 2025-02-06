#ifndef PHILO_H
# define PHILO_H

# ifndef MAX_INT
#  define MAX_INT 2147483647
# endif

typedef struct s_data	t_data;

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

/**
 * My structure to keep forks
 * 
 */
typedef struct s_fork
{
	pthread_mutex_t fork;
	int				fork_id;
}	t_fork;

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
}	t_philo;

/**
 * Program main structure
 * 
 */
struct s_data
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
	t_fork	*forks;
	t_philo	*philos;
};


void	parse_input(t_data *data, char *argv[]);
void	data_init(t_data *data);
void	ft_philo_error(t_philo_errors e_nb, t_data *data);
void	*ft_malloc(size_t bytes, t_data *data);
void	dinner_start(t_data *data);

void	set_bool(pthread_mutex_t *lock, bool *v, bool new_v);
bool	get_bool(pthread_mutex_t *lock, bool *v);
void	set_long(pthread_mutex_t *lock, long *v, long new_v);
long	get_long(pthread_mutex_t *lock, long *v);
bool	is_dinner_finished(t_data *data);

#endif
