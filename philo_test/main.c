#include "philo_one.h"

void	display(char *msg, t_phil *phil)
{
	long long	time;

	pthread_mutex_lock(&phil->args->display_block);
	if (!ft_strcmp(msg, "cycles ended"))
	{
		printf(BOLDGREEN"End of cycles\n"RESET"");
		exit(0);
	}
	time = get_time() - phil->args->start_time;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(phil->index, 1);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (!ft_strcmp(msg, "died"))
		exit(0);
	pthread_mutex_unlock(&phil->args->display_block);
}

void	*process(void *tmp)
{
	t_phil	*phil;

	phil = (t_phil *)tmp;
	if (!phil->last_eating)
		phil->last_eating = phil->args->start_time;
	pthread_mutex_lock(phil->left_fork);
	display("has taken a fork", phil);
	pthread_mutex_lock(phil->right_fork);
	pthread_mutex_lock(&phil->die);
	display("has taken a fork", phil);
	display("is eating", phil);
	phil->last_eating = get_time();
	usleep(1000 * phil->args->eat_time);
	pthread_mutex_unlock(phil->left_fork);
	pthread_mutex_unlock(phil->right_fork);
	pthread_mutex_unlock(&phil->die);
	phil->count++;
	sleeping(phil);
	return (0);
}

void	sleeping(t_phil *phil)
{
	display("is sleeping", phil);
	usleep(1000 * phil->args->sleep_time);
	display("is thinking", phil);
	process(phil);
}

void	start_threads(t_phil *phils, int n)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < phils->args->phil_count)
	{
		if (i % 2 == n)
		{
			pthread_create(&thread, NULL, process, (void *)&phils[i]);
			pthread_detach(thread);
		}
		i++;
	}
}

void	begin_simulation(t_phil *phils)
{
	int		i;
	int		end;

	phils->args->start_time = get_time();
	start_threads(phils, 0);
	start_threads(phils, 1);
	while (1)
	{
		i = 0;
		end = 1;
		while (i < phils->args->phil_count)
		{
			pthread_mutex_lock(&phils[i].die);
			if (get_time() - phils[i].last_eating > phils[i].args->die_time)
				display("died", &phils[i]);
			pthread_mutex_unlock(&phils[i].die);
			if (phils[i].count < phils[i].args->cycles)
				end = 0;
			i++;
		}
		if (end && phils->count && phils->args->cycles)
			display("cycles ended", phils);
	}
}

void	start(t_args *args)
{
	int				i;
	t_phil			phils[args->phil_count];
	pthread_mutex_t	forks[args->phil_count];

	i = 0;
	while (i < args->phil_count)
		pthread_mutex_init(&forks[i++], NULL);
	i = 0;
	while (i < args->phil_count)
	{
		pthread_mutex_init(&phils[i].die, NULL);
		phils[i].left_fork = &forks[i];
		if ((i + 1) > args->phil_count)
			phils[i].right_fork = &forks[0];
		else
			phils[i].right_fork = &forks[i + 1];
		phils[i].index = i;
		phils[i].count = 0;
		phils[i].args = args;
		phils[i].last_eating = 0;
		i++;
	}
	begin_simulation(phils);
}

void	args_init(t_args *args, char **argv, int argc)
{
	args->phil_count = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->cycles = 0;
	if (argc == 6)
		args->cycles = ft_atoi(argv[5]);
	pthread_mutex_init(&args->display_block, NULL);
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
