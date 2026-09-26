/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export_print.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/19 00:00:00 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:54:03 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	string_compare(char *first, char *second)
{
	int	i;

	i = 0;
	while (first[i] && first[i] == second[i])
		i++;
	return ((unsigned char)first[i] - (unsigned char)second[i]);
}

static void	sort_environment(char **env)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = i + 1;
		while (env[j])
		{
			if (string_compare(env[i], env[j]) > 0)
			{
				temp = env[i];
				env[i] = env[j];
				env[j] = temp;
			}
			j++;
		}
		i++;
	}
}

static void	print_export_entry(char *entry)
{
	int	i;

	i = 0;
	ft_putstr_fd("declare -x ", STDOUT_FILENO);
	while (entry[i] && entry[i] != '=')
	{
		write(STDOUT_FILENO, &entry[i], 1);
		i++;
	}
	if (entry[i] == '=')
	{
		write(STDOUT_FILENO, "=\"", 2);
		ft_putstr_fd(entry + i + 1, STDOUT_FILENO);
		write(STDOUT_FILENO, "\"", 1);
	}
	write(STDOUT_FILENO, "\n", 1);
}

int	print_export(char **env)
{
	char	**copy;
	int		i;

	copy = env_copy(env);
	if (!copy)
		return (1);
	sort_environment(copy);
	i = 0;
	while (copy[i])
	{
		print_export_entry(copy[i]);
		i++;
	}
	env_free(copy);
	return (0);
}
