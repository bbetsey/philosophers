#include "headers.h"

int	check_philosophers(t_phil *phils, int *end)
{
	int		i;

	i = 0;
	while (i < phils->args->phil_count)
	{
		sem_wait(phils->args->die);
		if (get_time() - phils[i].last_eating > phils[i].args->die_time)
		{
			display("died", &phils[i]);
			return (0);
		}
		sem_post(phils->args->die);
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
	start_threads(phils);
	while (1)
	{
		end = 1;
		res = check_philosophers(phils, &end);
		if (!res)
			return ;
		if (end && phils->args->cycles)
		{
			display("cycles ended", phils);
			return ;
		}
	}
}

void	start(t_args *args)
{
	int				i;
	t_phil			*phils;

	phils = malloc(sizeof(t_phil) * args->phil_count);
	sem_unlink("forks");
	sem_unlink("die");
	sem_unlink("display");
	sem_unlink("stop");
	args->forks = sem_open("forks", O_CREAT, 0644, args->phil_count);
	args->die = sem_open("die", O_CREAT, 0644, 1);
	args->display = sem_open("display", O_CREAT, 0644, 1);
	args->stop = sem_open("stop", O_CREAT, 0644, 1);
	i = 0;
	while (i < args->phil_count)
	{
		phils[i].index = i;
		phils[i].count = 0;
		phils[i].args = args;
		i++;
	}
	begin_simulation(phils);
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
