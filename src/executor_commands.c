/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 20:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/21 18:18:49 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_commands(t_shell *shell, t_exec_cmd *command)
{
	if (!command)
	{
		shell->last_status = 0;
		return (0);
	}
	if (!command->argv || !command->argv[0])
	{
		shell->last_status = 0;
		return (0);
	}
	if (command->next)
		return (execute_pipeline(shell, command));
	if (is_builtin(command->argv[0]))
		return (execute_builtin_redir(shell, command));
	return (execute_pipeline(shell, command));
}
