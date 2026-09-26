#include "minishell.h"

static size_t	ft_intlen(int n)
{
	size_t	len;
	long	value;

	len = 1;
	value = n;
	if (value < 0)
	{
		len++;
		value = -value;
	}
	while (value > 9)
	{
		len++;
		value = value / 10;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char	*str;
	size_t	len;
	size_t	i;
	long	value;

	value = n;
	len = ft_intlen(n);
	str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	if (value < 0)
		value = -value;
	str[len] = '\0';
	i = len;
	while (i > 0)
	{
		i--;
		str[i] = '0' + value % 10;
		value = value / 10;
	}
	if (n < 0)
		str[0] = '-';
	return (str);
}

int	ft_atoi(const char *nptr)
{
	long	number;
	int		sign;

	number = 0;
	sign = 1;
	while (*nptr == ' ' || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sign = -1;
		nptr++;
	}
	while (ft_isdigit(*nptr))
	{
		number = number * 10 + (*nptr - '0');
		nptr++;
	}
	return ((int)(number * sign));
}

void	ft_putstr_fd(char *s, int fd)
{
	if (s == NULL)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	ft_putstr_fd(s, fd);
	write(fd, "\n", 1);
}
