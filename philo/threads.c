#include "headers.h"

void	*process(void *tmp)
{
	t_phil		*phil;

	phil = (t_phil *)tmp;
	while (1)
	{
		pthread_mutex_lock(phil->left_fork);
		display(" has taken a fork\n", phil);
		pthread_mutex_lock(phil->right_fork);
		pthread_mutex_lock(&phil->die);
		phil->last_eating = get_time();
		pthread_mutex_unlock(&phil->die);
		display(" has taken a fork\n", phil);
		display(" is eating\n", phil);
		usleep(1000 * phil->args->eat_time);
		pthread_mutex_unlock(phil->right_fork);
		pthread_mutex_unlock(phil->left_fork);
		phil->count++;
		display(" is sleeping\n", phil);
		usleep(1000 * phil->args->sleep_time);
		display(" is thinking\n", phil);
	}
	return (0);
}

void	start_threads(t_phil *phils, int n)
{
	pthread_t	thread;

	while (n < phils->args->phil_count)
	{
		phils[n].last_eating = get_time();
		pthread_create(&thread, NULL, process, &phils[n]);
		pthread_detach(thread);
		n += 2;
	}
}
