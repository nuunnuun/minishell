/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 22:06:03 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/18 17:44:15 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <stdlib.h>
# include "libft.h"

typedef struct s_shell
{
	char	**env;
	int		last_status;
}	t_shell;

char	**env_copy(char **envp);
void	env_free(char **env);
char	*env_get(char **env, char *name);

#endif