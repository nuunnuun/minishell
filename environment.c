/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   environment.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/18 17:46:03 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:31:31 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	env_count(char **envp)
{
	size_t	count;

	count = 0;
	while (envp[count])
		count++;
	return (count);
}

void	env_free(char **env)
{
	size_t	i;

	if (!env)
		return ;
	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}

char	**env_copy(char **envp)
{
	char	**copy;
	size_t	i;

	copy = ft_calloc(env_count(envp) + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			env_free(copy);
			return (NULL);
		}
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

char	*env_get(char **env, char *name)
{
	size_t	i;
	size_t	name_len;

	i = 0;
	name_len = ft_strlen(name);
	while (env[i])
	{
		if (ft_strncmp(env[i], name, name_len) == 0
			&& env[i][name_len] == '=')
			return (env[i] + name_len + 1);
		i++;
	}
	return (NULL);
}

void	shell_init_env(t_shell *shell)
{
	char	*cwd;
	char	*cur;
	char	*value;
	int		n;

	env_unset(shell, "OLDPWD");
	cwd = getcwd(NULL, 0);
	if (cwd)
	{
		cur = env_get(shell->env, "PWD");
		if (!cur || ft_strncmp(cur, cwd, ft_strlen(cur) + 1) != 0)
			env_set(shell, "PWD", cwd);
		free(cwd);
	}
	cur = env_get(shell->env, "SHLVL");
	n = 0;
	if (cur)
		n = ft_atoi(cur);
	value = ft_itoa(n + 1);
	if (!value)
		return ;
	env_set(shell, "SHLVL", value);
	free(value);
}
