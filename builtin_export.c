/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:53:41 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_export_error(char *arg)
{
	ft_putstr_fd("minishell: export: `", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
}

static int	export_argument(t_shell *shell, char *arg)
{
	char	*equal;
	char	*name;
	int		status;

	equal = ft_strchr(arg, '=');
	if (equal)
		name = ft_substr(arg, 0, equal - arg);
	else
		name = ft_strdup(arg);
	if (!name)
		return (1);
	if (!is_valid_env_name(name))
	{
		print_export_error(arg);
		free(name);
		return (1);
	}
	status = 0;
	if (equal)
		status = env_set(shell, name, equal + 1);
	else
		status = env_set(shell, name, NULL);
	free(name);
	return (status);
}

int	builtin_export(t_shell *shell, char **argv)
{
	int	i;
	int	status;

	if (!argv[1])
		return (print_export(shell->env));
	i = 1;
	status = 0;
	while (argv[i])
	{
		if (export_argument(shell, argv[i]))
			status = 1;
		i++;
	}
	return (status);
}
