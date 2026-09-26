/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 18:30:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/23 18:44:47 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_command_pipe(t_exec_cmd *command, int pipe_fd[2])
{
	pipe_fd[0] = -1;
	pipe_fd[1] = -1;
	if (command->next && pipe(pipe_fd) == -1)
	{
		perror("minishell: pipe");
		return (1);
	}
	return (0);
}

static void	close_launch_fds(t_pipeline *pipeline, int pipe_fd[2])
{
	if (pipeline->input_fd != -1)
		close(pipeline->input_fd);
	if (pipe_fd[0] != -1)
		close(pipe_fd[0]);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipeline->input_fd = -1;
}

static int	launch_command(t_shell *shell, t_exec_cmd *command,
		t_pipeline *pipeline)
{
	int		pipe_fd[2];
	pid_t	pid;

	if (create_command_pipe(command, pipe_fd) != 0)
		return (1);
	pid = fork();
	if (pid == 0)
		pipeline_run_child(shell, command, pipeline->input_fd, pipe_fd);
	if (pid == -1)
	{
		perror("minishell: fork");
		close_launch_fds(pipeline, pipe_fd);
		return (1);
	}
	if (pipeline->input_fd != -1)
		close(pipeline->input_fd);
	if (pipe_fd[1] != -1)
		close(pipe_fd[1]);
	pipeline->input_fd = pipe_fd[0];
	pipeline->last_pid = pid;
	pipeline->child_count++;
	return (0);
}

static void	wait_previous_children(int child_count)
{
	while (child_count > 1)
	{
		wait(NULL);
		child_count--;
	}
}

int	execute_pipeline(t_shell *shell, t_exec_cmd *command)
{
	t_pipeline	pipeline;

	pipeline.input_fd = -1;
	pipeline.last_pid = -1;
	pipeline.child_count = 0;
	signals_parent_wait();
	while (command)
	{
		if (launch_command(shell, command, &pipeline) != 0)
		{
			wait_previous_children(pipeline.child_count + 1);
			signals_prompt();
			shell->last_status = 1;
			return (1);
		}
		command = command->next;
	}
	shell->last_status = executor_wait_child(pipeline.last_pid);
	wait_previous_children(pipeline.child_count);
	signals_prompt();
	return (shell->last_status);
}
