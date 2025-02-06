#include "philo.h"

void	*ft_malloc(size_t bytes, t_data *data)
{
	void	*result;

	result = malloc(bytes);
	if (result == NULL)
		ft_philo_error(MALLOC_ERROR, data);
	return (result);
}
