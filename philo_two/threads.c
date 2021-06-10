#include "headers.h"

void	*process(void *tmp)
{
	t_phil	*phil;

	phil = (t_phil *)tmp;
	while (1)
	{
		if (phil->args->cycles && phil->args->cycles == phil->count)
			return (0);
		sem_wait(phil->args->stop);
		sem_wait(phil->args->forks);
		display("has taken a fork", phil);
		sem_wait(phil->args->forks);
		sem_post(phil->args->stop);
		sem_wait(phil->args->die);
		display("has taken a fork", phil);
		display("is eating", phil);
		phil->last_eating = get_time();
		sem_post(phil->args->die);
		usleep(1000 * phil->args->eat_time);
		sem_post(phil->args->forks);
		sem_post(phil->args->forks);
		phil->count++;
		sleeping(phil);
	}
	return (0);
}

void	sleeping(t_phil *phil)
{
	display("is sleeping", phil);
	usleep(1000 * phil->args->sleep_time);
	display("is thinking", phil);
}

void	start_threads(t_phil *phils)
{
	pthread_t	thread;
	int			i;

	i = 0;
	while (i < phils->args->phil_count)
	{
		phils[i].last_eating = get_time();
		pthread_create(&thread, NULL, process, (void *)&phils[i]);
		pthread_detach(thread);
		i++;
	}
}
