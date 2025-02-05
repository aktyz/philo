#include "philo.h"

static void	how_to_run(void);

int	main (int argc, char *argv[])
{
	t_data	data;

	if (argc > 4 && argc < 7)
	{
		parse_input(&data, argv);
		data_init(&data);
		dinner_start(&data);
		clean(&data);
	}
	else
		how_to_run();
	return (0);
}

static void	how_to_run(void)
{
	printf("Incorrect number of arguments!\n");
	printf("Provide four or five arguments:\n");
	printf("nb_of_philosophers\ttime_to_die\ttime_to_eat\ttime_to_sleep\n");
	printf("\nOptional fifth argument:\n");
	printf("nb_of_times_each_philosopher_must_eat\n");
	ft_philo_error(INCORRECT_NB_ARGS);
}
