#include "philo.h"

static void	philo_init(t_data *data);
static void	assign_forks(t_philo *philo, t_fork	*forks, int i);

void	data_init(t_data *data)
{
	int	i;

	i = -1;
	data->is_end = false;
	data->philos = ft_malloc(data->nb_philos * sizeof(t_philo));
	data->forks = ft_malloc(data->nb_philos * sizeof(t_fork));
	while (++i < data->nb_philos)
	{
		pthread_mutex_init(&data->forks[i].fork, NULL);
		data->forks[i].fork_id = i;
	}
	philo_init(data);
}

static void	philo_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	while (++i < data->nb_philos)
	{
		philo = data->philos + i;
		philo->id = i + 1;
		philo->full = false;
		philo->meals_count = 0;
		philo->data = data;
		assign_forks(philo, data->forks, i);
	}
}

static void	assign_forks(t_philo *philo, t_fork	*forks, int pos)
{
	int	philo_nb;

	philo_nb = philo->data->nb_philos;
	if (philo->id % 2 == 0)
	{
		philo->first_fork = &forks[pos];
		philo->second_fork = &forks[(pos + 1) % philo_nb];
	}
	else
	{
		philo->first_fork = &forks[(pos + 1) % philo_nb];
		philo->second_fork = &forks[pos];
	}
}
