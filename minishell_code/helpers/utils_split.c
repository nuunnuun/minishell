#include "minishell.h"

static size_t	ft_word_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s == '\0')
			break ;
		count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static size_t	ft_word_len(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*ft_word_dup(const char *s, char c, const char **next)
{
	char	*word;
	size_t	len;
	size_t	i;

	len = ft_word_len(s, c);
	word = malloc(len + 1);
	if (word == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		word[i] = s[i];
		i++;
	}
	word[len] = '\0';
	*next = s + len;
	return (word);
}

static char	**ft_free_words(char **words, size_t i)
{
	while (i > 0)
	{
		i--;
		free(words[i]);
	}
	free(words);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**words;
	size_t	count;
	size_t	i;

	if (s == NULL)
		return (NULL);
	count = ft_word_count(s, c);
	words = malloc((count + 1) * sizeof(char *));
	if (words == NULL)
		return (NULL);
	i = 0;
	while (i < count)
	{
		while (*s && *s == c)
			s++;
		words[i] = ft_word_dup(s, c, &s);
		if (words[i] == NULL)
			return (ft_free_words(words, i));
		i++;
	}
	words[i] = NULL;
	return (words);
}
