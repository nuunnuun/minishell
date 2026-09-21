/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/21 10:52:10 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/21 17:52:29 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

static int	redirect_output(char *filename, int flags)
{
	int	fd;

	fd = open(filename, O_WRONLY | O_CREAT | flags, 0644);
	if (fd == -1)
	{
		perror(filename);
		return (1);
	}
	if (dup2(fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2");
		close(fd);
		return (1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(t_redirection *redirection)
{
	while (redirection)
	{
		if (redirection->type == REDIR_INPUT
			&& redirect_input(redirection->filename) != 0)
			return (1);
		if (redirection->type == REDIR_OUTPUT
			&& redirect_output(redirection->filename, O_TRUNC) != 0)
			return (1);
		if (redirection->type == REDIR_APPEND
			&& redirect_output(redirection->filename, O_APPEND) != 0)
			return (1);
		redirection = redirection->next;
	}
	return (0);
}
