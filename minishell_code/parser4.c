/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mserovat <mserovat@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/16 12:00:00 by mserovat       #+#    #+#             */
/*   Updated: 2026/09/16 12:00:00 by mserovat       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	empty_line_failure(const char *line, int *status)
{
	if (empty_line_check(line))
	{
		*status = 0;
		return (1);
	}
	return (0);
}

static t_command	*parsing_failure(t_token **tokens, int *status)
{
	*status = 1;
	free_token_list(tokens);
	return (NULL);
}

static t_command	*tokenization_failure(const char *line, int *status)
{
	t_quote_state	state;
	int				i;

	state = STATE_DEFAULT;
	i = 0;
	while (line[i] != '\0')
	{
		state = set_state(line[i], state);
		i++;
	}
	if (state != STATE_DEFAULT)
		*status = 2;
	else
		*status = 1;
	return (NULL);
}

static int	grammar_failure(t_token **tokens, int *status)
{
	if (check_grammar(*tokens))
	{
		*status = 2;
		free_token_list(tokens);
		return (1);
	}
	return (0);
}

t_command	*parse(const char *line, int *status)
{
	t_command	*commands;
	t_token		*tokens;

	if (empty_line_failure(line, status))
		return (NULL);
	tokens = build_token_list(line);
	if (!tokens)
		return (tokenization_failure(line, status));
	if (!deliver_token_list(&tokens, line))
		return (parsing_failure(&tokens, status));
	if (grammar_failure(&tokens, status))
		return (NULL);
	commands = build_command_list(tokens);
	if (!commands)
		return (parsing_failure(&tokens, status));
	*status = 0;
	free_token_list(&tokens);
	return (commands);
}
