/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/20 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/20 18:50:33 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_command_path(char *directory, char *command)
{
	char	*temporary;
	char	*full_path;

	temporary = ft_strjoin(directory, "/");
	if (!temporary)
		return (NULL);
	full_path = ft_strjoin(temporary, command);
	free(temporary);
	return (full_path);
}

static char	*search_path_directories(char **directories, char *command)
{
	char	*full_path;
	char	*blocked_path;
	size_t	i;

	i = 0;
	blocked_path = NULL;
	while (directories[i])
	{
		full_path = join_command_path(directories[i], command);
		if (!full_path)
			return (free(blocked_path), NULL);
		if (access(full_path, X_OK) == 0)
			return (free(blocked_path), full_path);
		if (!blocked_path && access(full_path, F_OK) == 0)
			blocked_path = full_path;
		else
			free(full_path);
		i++;
	}
	return (blocked_path);
}

char	*resolve_command_path(t_shell *shell, char *command)
{
	char	*path;
	char	**directories;
	char	*result;

	if (!command || !*command)
		return (NULL);
	if (ft_strchr(command, '/'))
		return (ft_strdup(command));
	path = env_get(shell->env, "PATH");
	if (!path)
		return (NULL);
	directories = ft_split(path, ':');
	if (!directories)
		return (NULL);
	result = search_path_directories(directories, command);
	env_free(directories);
	return (result);
}
