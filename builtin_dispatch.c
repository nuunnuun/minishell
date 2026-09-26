/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_dispatch.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 17:01:02 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(char *name)
{
	if (!name)
		return (0);
	if (ft_strncmp(name, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(name, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(name, "env", 4) == 0)
		return (1);
	if (ft_strncmp(name, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(name, "export", 7) == 0)
		return (1);
	if (ft_strncmp(name, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(name, "exit", 5) == 0)
		return (1);
	return (0);
}

static int	run_builtin(t_shell *shell, char **argv)
{
	if (ft_strncmp(argv[0], "echo", 5) == 0)
		return (builtin_echo(shell, argv));
	if (ft_strncmp(argv[0], "pwd", 4) == 0)
		return (builtin_pwd(shell, argv));
	if (ft_strncmp(argv[0], "env", 4) == 0)
		return (builtin_env(shell, argv));
	if (ft_strncmp(argv[0], "cd", 3) == 0)
		return (builtin_cd(shell, argv));
	if (ft_strncmp(argv[0], "export", 7) == 0)
		return (builtin_export(shell, argv));
	if (ft_strncmp(argv[0], "unset", 6) == 0)
		return (builtin_unset(shell, argv));
	return (builtin_exit(shell, argv));
}

int	execute_builtin(t_shell *shell, char **argv)
{
	int	status;

	if (!argv || !argv[0] || !is_builtin(argv[0]))
		return (-1);
	status = run_builtin(shell, argv);
	shell->last_status = status;
	return (status);
}
