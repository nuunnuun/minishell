#include "minishell.h"
#include <stdlib.h>

char	*expand_dollar(const char *line, int *i, int status, char *word,
			char **env);

char	*add_str(char *s1, const char *s2)
{
	char	*join;

	if (s2 == NULL)
		return (s1);
	join = ft_strjoin(s1, s2);
	free(s1);
	return (join);
}

static char	*add_char(char *word, char c)
{
	char	tmp[2];

	tmp[0] = c;
	tmp[1] = '\0';
	return (add_str(word, tmp));
}

static char	*expand_loop(const char *line, char *word, int status,
		char **env)
{
	int	i;
	t_quote_state	state;
	t_quote_state	new_state;

	i = 0;
	state = STATE_DEFAULT;
	while (line[i] && word != NULL)
	{
		new_state = set_state(line[i], state);
		if (new_state != state)
			state = new_state;
		else if (line[i] == '$' && state != STATE_SQUOTE)
		{
			word = expand_dollar(line, &i, status, word, env);
			continue ;
		}
		else
			word = add_char(word, line[i]);
		i++;
	}
	return (word);
}

char	*expand_word(const char *line, int status, char **env)
{
	char	*word;

	word = ft_strdup("");
	if (word == NULL)
		return (NULL);
	word = expand_loop(line, word, status, env);
	return (word);
}
