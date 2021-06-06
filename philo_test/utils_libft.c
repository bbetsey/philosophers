#include "philo_one.h"

static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' ||
		c == '\r' || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int		sign;
	long	result;
	long	next;

	sign = 1;
	result = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			sign *= -1;
		str++;
	}
	while (*str >= 48 && *str <= 57)
	{
		next = result * 10 + (*str - 48);
		if (next < result)
			return (sign < 0 ? 0 : -1);
		result = next;
		str++;
	}
	return (int)(result * sign);
}

void	ft_putchar_fd(char s, int fd)
{
	write(fd, &s, 1);
}

void	ft_putnbr_fd(long long n, int fd)
{
	long long	num;

	if (n < 0)
	{
		write(fd, "-", 1);
		num = -n;
	}
	else
		num = n;
	if (num >= 10)
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putnbr_fd(num % 10, fd);
	}
	else
		ft_putchar_fd(num + 48, fd);
}

int	ft_strlen(char *str)
{
	int		len;

	len = 0;
	if (!str)
		return (0);
	while (*str)
	{
		str++;
		len++;
	}
	return (len);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s1[i] == s2[i] && s1[i] != 0 && s2[i] != 0)
		i++;
	return (s1[i] - s2[i]);
}
