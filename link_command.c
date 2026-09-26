#include "minishell.h"

static char	**dup_argv(char **argv)
{
	char	**copy;
	int		n;
	int		i;

	n = 0;
	while (argv && argv[n])
		n++;
	copy = ft_calloc(n + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (i < n)
	{
		copy[i] = ft_strdup(argv[i]);
		if (!copy[i])
		{
			while (--i >= 0)
				free(copy[i]);
			free(copy);
			return (NULL);
		}
		i++;
	}
	return (copy);
}

static t_exec_cmd	*convert_one_cmd(t_command *src)
{
	t_exec_cmd	*dst;

	dst = ft_calloc(1, sizeof(t_exec_cmd));
	if (!dst)
		return (NULL);
	dst->argv = dup_argv(src->argv);
	if (!dst->argv)
	{
		free(dst);
		return (NULL);
	}
	dst->redirections = NULL;
	dst->next = NULL;
	if (convert_redirs(dst, src->redirs))
	{
		free_exec_cmd_list(dst);
		return (NULL);
	}
	return (dst);
}

t_exec_cmd	*convert_commands(t_command *cmds)
{
	t_exec_cmd	*head;
	t_exec_cmd	*tail;
	t_exec_cmd	*node;

	head = NULL;
	tail = NULL;
	while (cmds)
	{
		node = convert_one_cmd(cmds);
		if (!node)
		{
			free_exec_cmd_list(head);
			return (NULL);
		}
		if (!head)
			head = node;
		else
			tail->next = node;
		tail = node;
		cmds = cmds->next;
	}
	return (head);
}

static void	free_one_exec_cmd(t_exec_cmd *cmd)
{
	t_redirection	*r;
	t_redirection	*rtmp;
	int				i;

	i = 0;
	while (cmd->argv && cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
	r = cmd->redirections;
	while (r)
	{
		rtmp = r;
		r = r->next;
		free(rtmp->filename);
		if (rtmp->type == REDIR_HEREDOC && rtmp->fd >= 0)
			close(rtmp->fd);
		free(rtmp);
	}
	free(cmd);
}

void	free_exec_cmd_list(t_exec_cmd *list)
{
	t_exec_cmd	*tmp;

	while (list)
	{
		tmp = list;
		list = list->next;
		free_one_exec_cmd(tmp);
	}
}
