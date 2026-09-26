/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 22:06:15 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/26 00:00:00 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_shell(t_shell *shell, char **envp)
{
	shell->env = env_copy(envp);
	shell->last_status = 0;
	shell->should_exit = 0;
	shell->exit_status = 0;
	if (!shell->env)
		return ;
	shell_init_env(shell);
}

static void	update_signal_status(t_shell *shell)
{
	if (g_signal == SIGINT)
	{
		shell->last_status = 130;
		g_signal = 0;
	}
}

static int	capture_heredocs(t_command *cmds, t_shell *shell)
{
	t_redirect	*r;
	int			fd;

	while (cmds)
	{
		r = cmds->redirs;
		while (r)
		{
			if (r->rd_type == TOKEN_HEREDOC && r->fd < 0 && r->target)
			{
				fd = heredoc_open_fd(r->target, shell);
				if (fd < 0)
					return (1);
				r->fd = fd;
			}
			r = r->next;
		}
		cmds = cmds->next;
	}
	return (0);
}

static void	run_line(t_shell *shell, char *line)
{
	t_command	*cmds;
	t_exec_cmd	*exec;
	int			pstatus;

	cmds = parse(line, &pstatus);
	if (!cmds)
	{
		if (pstatus == 2 || pstatus == 1)
			shell->last_status = pstatus;
		else
			shell->last_status = 0;
		return ;
	}
	if (expand_commands(cmds, shell))
	{
		shell->last_status = 1;
		free_command_list(cmds);
		return ;
	}
	if (capture_heredocs(cmds, shell))
	{
		shell->last_status = 1;
		close_heredoc_fds(cmds);
		free_command_list(cmds);
		return ;
	}
	exec = convert_commands(cmds);
	if (!exec)
		close_heredoc_fds(cmds);
	free_command_list(cmds);
	if (!exec)
	{
		shell->last_status = 1;
		return ;
	}
	shell->last_status = execute_commands(shell, exec);
	free_exec_cmd_list(exec);
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
		{
			write(STDOUT_FILENO, "\n", 1);
			break ;
		}
		if (*line)
			add_history(line);
		if (*line)
			run_line(&shell, line);
		free(line);
	}
	env_free(shell.env);
	if (shell.should_exit)
		return (shell.exit_status);
	return (shell.last_status);
}
