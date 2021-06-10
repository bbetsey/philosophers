#include "headers.h"

int	check_philosophers(t_phil *phils, int *end)
{
	int		i;

	i = 0;
	while (i < phils->args->phil_count)
	{
		pthread_mutex_lock(&phils[i].die);
		if (get_time() - phils[i].last_eating > phils[i].args->die_time)
		{
			display(" died\n", &phils[i]);
			return (0);
		}
		pthread_mutex_unlock(&phils[i].die);
		if (phils[i].count < phils[i].args->cycles)
			*end = 0;
		i++;
	}
	return (1);
}

void	begin_simulation(t_phil *phils)
{
	int		res;
	int		end;

	phils->args->start_time = get_time();
	start_threads(phils, 0);
	usleep(1000);
	start_threads(phils, 1);
	while (1)
	{
		end = 1;
		res = check_philosophers(phils, &end);
		if (!res)
			return ;
		if (end && phils->args->cycles)
		{
			display_end(phils);
			return ;
		}
	}
}

void	start(t_args *args)
{
	int				i;
	t_phil			*phils;
	pthread_mutex_t	*forks;

	phils = malloc(sizeof(t_phil) * args->phil_count);
	forks = malloc(sizeof(pthread_mutex_t) * args->phil_count);
	i = 0;
	while (i < args->phil_count)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < args->phil_count)
	{
		pthread_mutex_init(&phils[i].die, NULL);
		phils[i].left_fork = &forks[i];
		phils[i].right_fork = &forks[(i + 1) % args->phil_count];
		phils[i].index = ft_itoa(i + 1);
		phils[i].count = 0;
		phils[i].args = args;
		i++;
	}
	begin_simulation(phils);
	free(forks);
	free(phils);
}

int	main(int argc, char **argv)
{
	t_args	args;

	if (argc < 5 || argc > 6)
	{
		printf("Error: \n");
		return (1);
	}
	args_init(&args, argv, argc);
	start(&args);
	return (0);
}
