/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_child.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 20:30:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/21 18:23:47 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_pipeline_child(t_shell *shell, int status)
{
	env_free(shell->env);
	exit(status);
}

static void	run_external_child(t_shell *shell, t_exec_cmd *command)
{
	char	*path;

	path = resolve_command_path(shell, command->argv[0]);
	if (!path)
	{
		ft_putstr_fd(command->argv[0], STDERR_FILENO);
		ft_putendl_fd(": command not found", STDERR_FILENO);
		exit_pipeline_child(shell, 127);
	}
	executor_run_child(shell, command->argv, path);
}

static void	close_child_fds(int input_fd, int pipe_fd[2])
{
	if (input_fd != -1)
		close(input_fd);
	if (pipe_fd[0] != -1 && pipe_fd[0] != input_fd)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
}

static void	run_child_command(t_shell *shell, t_exec_cmd *command)
{
	int	status;

	if (!command->argv || !command->argv[0])
		exit_pipeline_child(shell, 0);
	if (is_builtin(command->argv[0]))
	{
		status = execute_builtin(shell, command->argv);
		exit_pipeline_child(shell, status);
	}
	run_external_child(shell, command);
}

void	pipeline_run_child(t_shell *shell, t_exec_cmd *command,
		int input_fd, int pipe_fd[2])
{
	if (input_fd != -1
		&& dup2(input_fd, STDIN_FILENO) == -1)
		exit_pipeline_child(shell, 1);
	if (pipe_fd[1] != -1
		&& dup2(pipe_fd[1], STDOUT_FILENO) == -1)
		exit_pipeline_child(shell, 1);
	close_child_fds(input_fd, pipe_fd);
	if (apply_redirections(command->redirections) != 0)
		exit_pipeline_child(shell, 1);
	run_child_command(shell, command);
}
