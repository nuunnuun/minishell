/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/23 18:43:12 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	command_not_found(t_shell *shell, char *command)
{
	ft_putstr_fd(command, 2);
	ft_putendl_fd(": command not found", 2);
	shell->last_status = 127;
	return (127);
}

static int	fork_failed(t_shell *shell, char *path)
{
	perror("minishell: fork");
	free(path);
	shell->last_status = 1;
	return (1);
}

static int	is_directory(char *path)
{
	struct stat	info;

	if (stat(path, &info) == 0 && S_ISDIR(info.st_mode))
		return (1);
	return (0);
}

static int	directory_error(t_shell *shell, char *path)
{
	ft_putstr_fd(path, 2);
	ft_putendl_fd(": Is a directory", 2);
	free(path);
	shell->last_status = 126;
	return (126);
}

int	execute_external(t_shell *shell, char **argv)
{
	char	*path;
	pid_t	pid;

	if (!argv || !argv[0])
		return (0);
	path = resolve_command_path(shell, argv[0]);
	if (!path)
		return (command_not_found(shell, argv[0]));
	if (is_directory(path))
		return (directory_error(shell, path));
	signals_parent_wait();
	pid = fork();
	if (pid == -1)
	{
		signals_prompt();
		return (fork_failed(shell, path));
	}
	if (pid == 0)
		executor_run_child(shell, argv, path);
	free(path);
	shell->last_status = executor_wait_child(pid);
	signals_prompt();
	return (shell->last_status);
}
