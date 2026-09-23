/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 22:06:15 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/23 18:25:12 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_copy(envp);
	shell->last_status = 0;
	shell->should_exit = 0;
	shell->exit_status = 0;
}

static void	update_signal_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_shell	shell;
	char	*line;

	(void)argc;
	(void)argv;
	init_shell(&shell, envp);
	if (!shell.env)
		return (1);
	signals_prompt();
	while (!shell.should_exit)
	{
		line = readline("minishell$ ");
		update_signal_status(&shell);
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
