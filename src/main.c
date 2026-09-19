/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 22:06:15 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:58:44 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	shell.env = env_copy(envp);
	if (!shell.env)
		return (1);
	shell.last_status = 0;
	shell.should_exit = 0;
	shell.exit_status = 0;
	while (!shell.should_exit)
	{
		line = readline("minishell$ ");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		free(line);
	}
	env_free(shell.env);
	if (shell.should_exit)
		return (shell.exit_status);
	return (shell.last_status);
}
