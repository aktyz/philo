#include "philo.h"

/**
 * SPINLOCK to sync all threads - wait for all threads creation
 *
 */
void	all_threads_ready(t_data *data)
{
	while(!get_bool(&data->data_mutex, &data->are_threads_ready))
		;
}