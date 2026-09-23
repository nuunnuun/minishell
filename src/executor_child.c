/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/23 19:01:33 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	executor_wait_child(pid_t pid)
{
	int	status;
	int	signal;

	if (waitpid(pid, &status, 0) == -1)
	{
		perror("minishell: waitpid");
		return (1);
	}
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	if (WIFSIGNALED(status))
	{
		signal = WTERMSIG(status);
		if (signal == SIGINT)
			write(STDOUT_FILENO, "\n", 1);
		else if (signal == SIGQUIT)
			write(STDERR_FILENO, "Quit: 3\n", 8);
		return (128 + signal);
	}
	return (1);
}

void	executor_run_child(t_shell *shell, char **argv, char *path)
{
	int	status;

	signals_child_default();
	execve(path, argv, shell->env);
	status = 126;
	if (errno == ENOENT)
		status = 127;
	perror(argv[0]);
	free(path);
	env_free(shell->env);
	exit(status);
}
