/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_builtin_redir.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 12:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/21 17:56:00 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	save_standard_fds(int backup[2])
{
	backup[0] = dup(STDIN_FILENO);
	if (backup[0] == -1)
	{
		perror("minishell: dup");
		return (1);
	}
	backup[1] = dup(STDOUT_FILENO);
	if (backup[1] == -1)
	{
		perror("minishell: dup");
		close(backup[0]);
		return (1);
	}
	return (0);
}

static int	restore_standard_fds(int backup[2])
{
	int	status;

	status = 0;
	if (dup2(backup[0], STDIN_FILENO) == -1)
		status = 1;
	if (dup2(backup[1], STDOUT_FILENO) == -1)
		status = 1;
	close(backup[0]);
	close(backup[1]);
	if (status != 0)
		perror("minishell: dup2");
	return (status);
}

int	execute_builtin_redir(t_shell *shell, t_exec_cmd *command)
{
	int	backup[2];
	int	status;

	if (save_standard_fds(backup) != 0)
	{
		shell->last_status = 1;
		return (1);
	}
	if (apply_redirections(command->redirections) != 0)
		status = 1;
	else
		status = execute_builtin(shell, command->argv);
	if (restore_standard_fds(backup) != 0)
		status = 1;
	shell->last_status = status;
	return (status);
}
