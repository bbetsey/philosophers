#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>

# define RESET			"\033[0m"
# define BLACK			"\033[30m"
# define RED			"\033[31m"
# define GREEN			"\033[32m"
# define YELLOW			"\033[33m"
# define BLUE			"\033[34m"
# define MAGENTA		"\033[35m"
# define CYAN			"\033[36m"
# define WHITE			"\033[37m"
# define BOLDBLACK		"\033[1m\033[30m"
# define BOLDRED		"\033[1m\033[31m"
# define BOLDGREEN		"\033[1m\033[32m"
# define BOLDYELLOW		"\033[1m\033[33m"
# define BOLDBLUE		"\033[1m\033[34m"
# define BOLDMAGENTA	"\033[1m\033[35m"
# define BOLDCYAN		"\033[1m\033[36m"
# define BOLDWHITE		"\033[1m\033[37m"

typedef struct s_args
{
	int				phil_count;
	int				die_time;
	int				eat_time;
	int				sleep_time;
	int				cycles;
	long long		start_time;
	pthread_mutex_t display_block;
}					t_args;

typedef struct s_phil
{
	t_args			*args;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t die;
	long long		last_eating;
	int				count;
	int				index;
}					t_phil;

// main
void				sleeping(t_phil *phil);

// utils
long long 			get_time(void);

// utils_libft
int					ft_atoi(char *str);
void				ft_putnbr_fd(long long n, int fd);
int					ft_strlen(char *str);
int					ft_strcmp(char *s1, char *s2);

#endif
