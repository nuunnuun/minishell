/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 22:06:03 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/19 16:57:27 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include "libft.h"
# include <unistd.h>

typedef struct s_shell
{
	char	**env;
	int		last_status;
	int		should_exit;
	int		exit_status;
}	t_shell;

char	**env_copy(char **envp);
void	env_free(char **env);
char	*env_get(char **env, char *name);

int		is_builtin(char *name);
int		execute_builtin(t_shell *shell, char **argv);
int		builtin_echo(t_shell *shell, char **argv);
int		builtin_pwd(t_shell *shell, char **argv);
int		builtin_env(t_shell *shell, char **argv);
int		builtin_cd(t_shell *shell, char **argv);
int		builtin_export(t_shell *shell, char **argv);
int		builtin_unset(t_shell *shell, char **argv);
int		builtin_exit(t_shell *shell, char **argv);
int		env_set(t_shell *shell, char *name, char *value);
void	env_unset(t_shell *shell, char *name);
int		is_valid_env_name(char *name);
int		print_export(char **env);

#endif