#include "headers.h"

void	waiting(t_phil *phils)
{
	int		status;
	int		count;

	count = 0;
	status = 0;
	while (status == 0 && count < phils->args->phil_count)
	{
		waitpid(-1, &status, 0);
		status = WEXITSTATUS(status);
		count++;
	}
	count = 0;
	while (count < phils->args->phil_count)
	{
		kill(phils[count].pid, SIGKILL);
		count++;
	}
}

void	begin_simulation(t_phil *phils)
{
	int		i;

	phils->args->start_time = get_time();
	i = 0;
	while (i < phils->args->phil_count)
	{
		phils[i].pid = fork();
		if (phils[i].pid == 0)
			start_thread(&phils[i]);
		i++;
	}
	waiting(phils);
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
		phils[i].index = ft_itoa(i + 1);
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
		printf(BOLDRED"Error:"RESET" wrong number of arguments\n");
		return (1);
	}
	if (!args_init(&args, argv, argc))
		return (1);
	start(&args);
	return (0);
}
