/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_exit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:57:54 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

static int	skip_exit_blanks(char *arg, int i)
{
	while (arg[i] == ' ' || (arg[i] >= '\t' && arg[i] <= '\r'))
		i++;
	return (i);
}

static int	read_exit_number(char *arg, unsigned long long *number, int *sign)
{
	int					i;
	unsigned long long	limit;

	i = 0;
	*sign = 1;
	i = skip_exit_blanks(arg, i);
	if (arg[i] == '+' || arg[i] == '-')
	{
		if (arg[i++] == '-')
			*sign = -1;
	}
	if (!arg[i])
		return (0);
	limit = LLONG_MAX;
	if (*sign < 0)
		limit++;
	*number = 0;
	while (arg[i] >= '0' && arg[i] <= '9')
	{
		if (*number > (limit - (arg[i] - '0')) / 10)
			return (0);
		*number = (*number * 10) + (arg[i++] - '0');
	}
	i = skip_exit_blanks(arg, i);
	return (arg[i] == '\0');
}

static int	exit_code(char *arg, int *valid)
{
	unsigned long long	number;
	int					sign;
	int					code;

	*valid = read_exit_number(arg, &number, &sign);
	if (!*valid)
		return (255);
	code = number % 256;
	if (sign < 0 && code != 0)
		code = 256 - code;
	return (code);
}

static void	print_numeric_error(char *arg)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd(": numeric argument required", STDERR_FILENO);
}

int	builtin_exit(t_shell *shell, char **argv)
{
	int	code;
	int	valid;

	ft_putendl_fd("exit", STDERR_FILENO);
	if (!argv[1])
		code = shell->last_status;
	else
		code = exit_code(argv[1], &valid);
	if (argv[1] && !valid)
		print_numeric_error(argv[1]);
	else if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: exit: too many arguments", STDERR_FILENO);
		return (1);
	}
	shell->should_exit = 1;
	shell->exit_status = code;
	return (code);
}
