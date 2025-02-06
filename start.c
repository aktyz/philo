#include "philo.h"

void	dinner_start(t_data *data)
{
	int	i;

	i = -1;
	if (data->min_eat == 0)
		return ;
	else if (data->nb_philos == 1)
		;//todo
	else
	{
		while (++i < data->nb_philos)
			pthread_create(&data->philos[i].thread_id, philo_task, &data->philos[i], NULL);
	}
	
	set_bool(&data->data_mutex, data->are_threads_ready, true);
}

void	*philo_task(void *data)
{
	t_philo *philo;

	philo = (t_philo *)data;
	all_threads_ready(philo->data); //TODO
}