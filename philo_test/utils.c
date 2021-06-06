#include "philo_one.h"

long long	get_time(void)
{
	struct timeval	now_time;
	long long		milisec;

	gettimeofday(&now_time, NULL);
	milisec = (now_time.tv_sec * 1000) + (now_time.tv_usec / 1000);
	return (milisec);
}
