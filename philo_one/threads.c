#include "philo_one.h"

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
