#ifndef HEADERS_H
# define HEADERS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <string.h>
# include <err.h>
# include <errno.h>
# include <semaphore.h>
# include <signal.h>

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
	sem_t			*display;
	sem_t			*die;
	sem_t			*forks;
	sem_t			*stop;
}					t_args;

typedef struct s_phil
{
	t_args			*args;
	pid_t			pid;
	long long		last_eating;
	int				count;
	char			*index;
}					t_phil;

// threads
void				start_thread(t_phil *phils);
void				sleeping(t_phil *phil);
void				*process(void *tmp);

// utils
long long			get_time(void);
void				display(char *msg, t_phil *phil);
int					ft_strcmp(char *s1, char *s2);
int					args_init(t_args *args, char **argv, int argc);
void				display_end(t_phil *phil);

// utils_libft
char				*ft_itoa(int n);
int					ft_atoi(char *str);
int					ft_strlen(char *str);
char				*ft_strjoin(char *s1, char *s2);

#endif
