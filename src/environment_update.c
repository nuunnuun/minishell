/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment_update.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:35:08 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_size(char **env)
{
	size_t	size;

	size = 0;
	while (env[size])
		size++;
	return (size);
}

static int	env_index(char **env, char *name)
{
	int		i;
	size_t	len;

	i = 0;
	len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static char	*make_env_entry(char *name, char *value)
{
	char	*prefix;
	char	*entry;

	prefix = ft_strjoin(name, "=");
	if (!prefix)
		return (NULL);
	entry = ft_strjoin(prefix, value);
	free(prefix);
	return (entry);
}

static int	append_env(t_shell *shell, char *entry)
{
	char	**new_env;
	size_t	size;
	size_t	i;

	size = env_size(shell->env);
	new_env = ft_calloc(size + 2, sizeof(char *));
	if (!new_env)
		return (1);
	i = 0;
	while (i < size)
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[size] = entry;
	free(shell->env);
	shell->env = new_env;
	return (0);
}

int	env_set(t_shell *shell, char *name, char *value)
{
	char	*entry;
	int		index;

	entry = make_env_entry(name, value);
	if (!entry)
		return (1);
	index = env_index(shell->env, name);
	if (index >= 0)
	{
		free(shell->env[index]);
		shell->env[index] = entry;
		return (0);
	}
	if (append_env(shell, entry))
		return (free(entry), 1);
	return (0);
}
