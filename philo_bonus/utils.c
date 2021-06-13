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

int	args_init(t_args *args, char **argv, int argc)
{
	args->phil_count = ft_atoi(argv[1]);
	args->die_time = ft_atoi(argv[2]);
	args->eat_time = ft_atoi(argv[3]);
	args->sleep_time = ft_atoi(argv[4]);
	args->cycles = 0;
	if (argc == 6)
	{
		args->cycles = ft_atoi(argv[5]);
		if (!args->cycles)
			return (0);
	}
	if (args->phil_count < 2 || args->phil_count > 200
		|| args->die_time < 1 || args->eat_time < 1 || args->sleep_time < 1)
		return (0);
	return (1);
}

void	display(char *msg, t_phil *phil)
{
	char	*str;

	sem_wait(phil->args->display);
	str = ft_itoa(get_time() - phil->args->start_time);
	str = ft_strjoin(str, phil->index);
	str = ft_strjoin(str, msg);
	write(1, str, ft_strlen(str));
	if (!ft_strcmp(msg, " died\n"))
		exit(1);
	sem_post(phil->args->display);
}

void	display_end(t_phil *phil)
{
	sem_wait(phil->args->display);
	printf(BOLDGREEN"End of cycles"BOLDMAGENTA" [%d:%d]\n"RESET"",
		phil->args->cycles, phil->args->cycles * phil->args->phil_count);
	exit(1);
}
