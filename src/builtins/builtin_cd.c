/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:53:14 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

static char	*get_cd_target(t_shell *shell, char **argv)
{
	char	*target;

	if (!argv[1])
	{
		target = env_get(shell->env, "HOME");
		if (!target)
			ft_putendl_fd("minishell: cd: HOME not set", STDERR_FILENO);
		return (target);
	}
	if (ft_strncmp(argv[1], "-", 2) == 0)
	{
		target = env_get(shell->env, "OLDPWD");
		if (!target)
			ft_putendl_fd("minishell: cd: OLDPWD not set", STDERR_FILENO);
		return (target);
	}
	return (argv[1]);
}

static int	update_directories(t_shell *shell, char *old_pwd, int print)
{
	char	*new_pwd;
	int		status;

	status = 0;
	new_pwd = getcwd(NULL, 0);
	if (old_pwd && env_set(shell, "OLDPWD", old_pwd))
		status = 1;
	if (new_pwd && env_set(shell, "PWD", new_pwd))
		status = 1;
	if (print && new_pwd)
		ft_putendl_fd(new_pwd, STDOUT_FILENO);
	free(old_pwd);
	free(new_pwd);
	return (status);
}

int	builtin_cd(t_shell *shell, char **argv)
{
	char	*old_pwd;
	char	*target;
	int		print;

	if (argv[1] && argv[2])
	{
		ft_putendl_fd("minishell: cd: too many arguments", STDERR_FILENO);
		return (1);
	}
	target = get_cd_target(shell, argv);
	if (!target)
		return (1);
	old_pwd = getcwd(NULL, 0);
	if (chdir(target) != 0)
	{
		perror("minishell: cd");
		free(old_pwd);
		return (1);
	}
	print = (argv[1] && ft_strncmp(argv[1], "-", 2) == 0);
	return (update_directories(shell, old_pwd, print));
}
