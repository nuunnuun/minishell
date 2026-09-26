#include "minishell.h"

int	write_body_line(int fd_w, char *line, int quoted, t_shell *shell)
{
	char	*exp;

	if (quoted)
	{
		ft_putendl_fd(line, fd_w);
		return (0);
	}
	exp = expand_word(line, shell->last_status, shell->env);
	if (!exp)
		return (1);
	ft_putendl_fd(exp, fd_w);
	free(exp);
	return (0);
}

static t_redir_type	map_type(int token_type)
{
	if (token_type == TOKEN_RD_IN)
		return (REDIR_INPUT);
	if (token_type == TOKEN_APPEND)
		return (REDIR_APPEND);
	if (token_type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_OUTPUT);
}

static t_redirection	*convert_one_redir(t_redirect *r)
{
	t_redirection	*out;

	out = ft_calloc(1, sizeof(t_redirection));
	if (!out)
		return (NULL);
	out->type = map_type(r->rd_type);
	out->fd = -1;
	if (out->type == REDIR_HEREDOC)
	{
		out->filename = NULL;
		out->fd = r->fd;
		r->fd = -1;
	}
	else
	{
		out->filename = ft_strdup(r->target);
		if (!out->filename)
		{
			free(out);
			return (NULL);
		}
	}
	out->next = NULL;
	return (out);
}

int	convert_redirs(t_exec_cmd *dst, t_redirect *src)
{
	t_redirection	*tail;
	t_redirection	*node;

	tail = NULL;
	while (src)
	{
		node = convert_one_redir(src);
		if (!node)
			return (1);
		if (!dst->redirections)
			dst->redirections = node;
		else
			tail->next = node;
		tail = node;
		src = src->next;
	}
	return (0);
}

void	close_heredoc_fds(t_command *cmds)
{
	t_redirect	*r;

	while (cmds)
	{
		r = cmds->redirs;
		while (r)
		{
			if (r->rd_type == TOKEN_HEREDOC && r->fd >= 0)
			{
				close(r->fd);
				r->fd = -1;
			}
			r = r->next;
		}
		cmds = cmds->next;
	}
}
