#include "minishell.h"

static int	expand_one_word(char **slot, t_shell *shell, int *removed)
{
	char	*raw;
	char	*expanded;

	raw = *slot;
	*removed = 0;
	expanded = expand_word(raw, shell->last_status, shell->env);
	if (!expanded)
		return (1);
	if (expanded[0] == '\0' && is_bare_expansion(raw))
	{
		free(raw);
		free(expanded);
		*slot = NULL;
		*removed = 1;
		return (0);
	}
	free(raw);
	*slot = expanded;
	return (0);
}

static int	expand_argv(t_command *cmd, t_shell *shell)
{
	int	i;
	int	j;
	int	removed;

	i = 0;
	j = 0;
	while (cmd->argv && cmd->argv[i])
	{
		if (expand_one_word(&cmd->argv[i], shell, &removed))
			return (1);
		if (!removed)
			cmd->argv[j++] = cmd->argv[i];
		i++;
	}
	if (cmd->argv)
		cmd->argv[j] = NULL;
	return (0);
}

static int	expand_redirs(t_command *cmd, t_shell *shell)
{
	t_redirect	*r;
	char		*expanded;

	r = cmd->redirs;
	while (r)
	{
		if (r->rd_type != TOKEN_HEREDOC && r->target)
		{
			expanded = expand_word(r->target, shell->last_status,
					shell->env);
			if (!expanded)
				return (1);
			if (expanded[0] == '\0')
			{
				ft_putendl_fd("minishell: ambiguous redirect", STDERR_FILENO);
				free(expanded);
				return (1);
			}
			free(r->target);
			r->target = expanded;
		}
		r = r->next;
	}
	return (0);
}

int	expand_commands(t_command *cmds, t_shell *shell)
{
	while (cmds)
	{
		if (expand_argv(cmds, shell))
			return (1);
		if (expand_redirs(cmds, shell))
			return (1);
		cmds = cmds->next;
	}
	return (0);
}
