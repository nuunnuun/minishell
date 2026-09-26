#include "minishell.h"

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	skip_bare_name(const char *raw, int i)
{
	if (raw[i + 1] == '?')
		return (i + 2);
	i++;
	while (ft_isalnum(raw[i]) || raw[i] == '_')
		i++;
	return (i);
}
