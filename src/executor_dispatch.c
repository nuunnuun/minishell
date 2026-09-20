/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_dispatch.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/21 00:44:57 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_command(t_shell *shell, char **argv)
{
	if (!argv || !argv[0])
	{
		shell->last_status = 0;
		return (0);
	}
	if (is_builtin(argv[0]))
		return (execute_builtin(shell, argv));
	return (execute_external(shell, argv));
}
