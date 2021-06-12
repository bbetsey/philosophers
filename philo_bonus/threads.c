#include "headers.h"

void	*process(void *tmp)
{
	t_phil	*phil;

	phil = (t_phil *)tmp;
	while (1)
	{
		if (phil->args->cycles && phil->args->cycles == phil->count)
			display_end(phil);
		sem_wait(phil->args->stop);
		sem_wait(phil->args->forks);
		display(" has taken a fork\n", phil);
		sem_wait(phil->args->forks);
		sem_post(phil->args->stop);
		sem_wait(phil->args->die);
		display(" has taken a fork\n", phil);
		display(" is eating\n", phil);
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
	display(" is sleeping\n", phil);
	usleep(1000 * phil->args->sleep_time);
	display(" is thinking\n", phil);
}

void	start_thread(t_phil *phil)
{
	pthread_t	thread;

	phil->last_eating = get_time();
	pthread_create(&thread, NULL, process, (void *)phil);
	pthread_detach(thread);
	while (1)
	{
		sem_wait(phil->args->die);
		if (get_time() - phil->last_eating > phil->args->die_time)
			display(" died\n", phil);
		sem_post(phil->args->die);
	}
}
