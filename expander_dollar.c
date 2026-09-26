#include "minishell.h"
#include <stdlib.h>

char	*add_str(char *s1, const char *s2);

static int	is_literal_dollar(char c)
{
	if (c == '\0' || c == ' ' || c == '\t')
		return (1);
	if (c == '"' || c == '\'')
		return (1);
	if (!ft_isalpha(c) && c != '_')
		return (1);
	return (0);
}

static char	*expand_status(int status, char *word)
{
	char	*value;

	value = ft_itoa(status);
	if (value == NULL)
	{
		free(word);
		return (NULL);
	}
	word = add_str(word, value);
	free(value);
	return (word);
}

static char	*expand_name(const char *line, int *i, char *word, char **env)
{
	char	*name;
	char	*value;
	int	start;
	int	len;

	start = *i + 1;
	len = 0;
	while (ft_isalnum(line[start + len]) || line[start + len] == '_')
		len++;
	name = ft_substr(line, start, len);
	if (name == NULL)
	{
		free(word);
		return (NULL);
	}
	value = env_get(env, name);
	if (value != NULL)
		word = add_str(word, value);
	free(name);
	*i = start + len;
	return (word);
}

char	*expand_dollar(const char *line, int *i, int status, char *word,
		char **env)
{
	if (line[*i + 1] == '?')
	{
		word = expand_status(status, word);
		*i += 2;
		return (word);
	}
	if (is_literal_dollar(line[*i + 1]))
	{
		word = add_str(word, "$");
		(*i)++;
		return (word);
	}
	return (expand_name(line, i, word, env));
}

int	is_bare_expansion(const char *raw)
{
	t_quote_state	state;
	t_quote_state	next;
	int				i;
	int				saw;

	state = STATE_DEFAULT;
	saw = 0;
	i = 0;
	while (raw[i])
	{
		next = set_state(raw[i], state);
		if (next != state)
			return (0);
		if (raw[i] != '$' || state == STATE_SQUOTE)
			return (0);
		if (is_literal_dollar(raw[i + 1]))
			return (0);
		saw = 1;
		i = skip_bare_name(raw, i);
	}
	return (saw);
}
