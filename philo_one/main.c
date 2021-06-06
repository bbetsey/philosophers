#include "philo_one.h"

int	main(int argc, char **argv)
{
	t_args		args;

	if (argc < 5 || argc > 6)
	{
		printf("Error\n");
		return (1);
	}
	args_init(&args);
	start_loop(&args);
	return (0);
}
