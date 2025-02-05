#include "philo.h"

static long			ft_atol(const char *str);
static const char	*valid_input(const char *str);
static inline bool	is_space(char c);
static inline bool	is_digit(char c);

void	parse_input(t_data *data, char *argv[])
{
	data->nb_philos = ft_atol(argv[1]);
	data->die_time = ft_atol(argv[2]) * 1e3;
	data->eat_time = ft_atol(argv[3]) * 1e3;
	data->sleep_time = ft_atol(argv[4]) * 1e3;
	if (argv[5])
		data->min_eat = ft_atol(argv[5]);
	else
		data->min_eat = -1;
}

static long	ft_atol(const char *str)
{
	long	result;

	result = 0;
	str = valid_input(str);
	while (is_digit(*str))
		result = (result * 10) + (*str - 48);
	if (result > INT_MAX)
		ft_philo_error(ATOI_ERROR);
	return (result);
}

/**
 * Function checking input number for:
 * - not being negative
 * - correct number
 * - not overflowing int min or max
 */
static const char	*valid_input(const char *str)
{
	int	len;
	const char *result;

	len = 0;
	while (is_space(*str))
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
		ft_philo_error(ATOI_ERROR);
	if (!is_digit(*str))
		ft_philo_error(ATOI_ERROR);
	result = str;
	while (is_digit(*str++))
		len++;
	if (len > 10)
		ft_philo_error(ATOI_ERROR);
	return (result);
}

static inline bool	is_space(char c)
{
	return ((c >= 9 && c <= 13) || 32 == c);
}

static inline bool	is_digit(char c)
{
	return (c > 47 && c < 58);
}
