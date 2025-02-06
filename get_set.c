#include "philo.h"

void	set_bool(pthread_mutex_t *lock, bool *v, bool new_v)
{
	pthread_mutex_lock(lock);
	v = new_v;
	pthread_mutex_unlock(lock);
}

bool	get_bool(pthread_mutex_t *lock, bool *v)
{
	bool	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

void	set_long(pthread_mutex_t *lock, long *v, long new_v)
{
	pthread_mutex_lock(lock);
	v = new_v;
	pthread_mutex_unlock(lock);
}

long	get_long(pthread_mutex_t *lock, long *v)
{
	long	result;

	pthread_mutex_lock(lock);
	result = *v;
	pthread_mutex_unlock(lock);
	return (result);
}

bool	is_dinner_finished(t_data *data)
{
	return (get_bool(&data->data_mutex, data->is_end));
}
