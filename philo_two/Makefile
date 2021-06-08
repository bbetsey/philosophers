NAME	= philo_two

SRCS	= main.c \
			threads.c \
			utils.c \
			utils_libft.c

OBJS	= $(SRCS:c=o)
FLAGS	= -O3 -Wall -Wextra -Werror -fsanitize=address

all: $(NAME)

$(NAME): $(OBJS)
	gcc $(FLAGS) -o $(NAME) $(OBJS) -pthread

%.o: %.c
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME)

re: fclean all

norm:
	norminette .
