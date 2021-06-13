#include "headers.h"

static int	ft_intsize(int n)
{
	int		len;

	len = 1;
	while (n / 10)
	{
		len++;
		n /= 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	int				len;
	unsigned int	nbr;
	char			*str;
	char			*buf;

	len = ft_intsize(n);
	str = malloc((len + 2) * sizeof(char));
	if (!str)
		return (0);
	str[len + 1] = '\0';
	str[len] = ' ';
	nbr = n;
	buf = str;
	*(str + len - 1) = nbr % 10 + 48;
	nbr /= 10;
	while (nbr)
	{
		*(str + len - 2) = nbr % 10 + 48;
		str--;
		nbr /= 10;
	}
	return (buf);
}
