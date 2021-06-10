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
	pthread_mutex_init(&args->display_block, NULL);
}

void	display(char *msg, t_phil *phil)
{
	char	*str;

	str = ft_itoa(get_time() - phil->args->start_time);
	str = ft_strjoin(str, phil->index);
	str = ft_strjoin(str, msg);
	pthread_mutex_lock(&phil->args->display_block);
	write(1, str, ft_strlen(str));
	if (!ft_strcmp(msg, " died\n"))
		return ;
	pthread_mutex_unlock(&phil->args->display_block);
}

void	display_end(t_phil *phil)
{
	pthread_mutex_lock(&phil->args->display_block);
	printf(BOLDGREEN"End of cycles\n"RESET"");
}