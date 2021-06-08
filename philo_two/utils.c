#include "headers.h"

long long	get_time(void)
{
	struct timeval	now_time;
	long long		milisec;

	gettimeofday(&now_time, NULL);
	milisec = (now_time.tv_sec * 1000) + (now_time.tv_usec / 1000);
	return (milisec);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (s1[i] - s2[i]);
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
}

void	display(char *msg, t_phil *phil)
{
	long long	time;

	sem_wait(phil->args->display);
	if (!ft_strcmp(msg, "cycles ended"))
	{
		printf(BOLDGREEN"End of cycles\n"RESET"");
		return ;
	}
	time = get_time() - phil->args->start_time;
	ft_putnbr_fd(time, 1);
	write(1, " ", 1);
	ft_putnbr_fd(phil->index + 1, 1);
	write(1, " ", 1);
	write(1, msg, ft_strlen(msg));
	write(1, "\n", 1);
	if (!ft_strcmp(msg, "died"))
		return ;
	sem_post(phil->args->display);
}
