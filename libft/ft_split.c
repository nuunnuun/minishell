/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kraksana <kraksana@student.42bangkok.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/07 18:18:18 by kraksana          #+#    #+#             */
/*   Updated: 2026/09/07 18:18:19 by kraksana         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	word_count(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	free_words(char **words, size_t count)
{
	while (count > 0)
		free(words[--count]);
	free(words);
}

static int	add_word(char **words, size_t *index,
		char const *s, size_t length)
{
	words[*index] = ft_substr(s, 0, length);
	if (!words[*index])
	{
		free_words(words, *index);
		return (0);
	}
	(*index)++;
	return (1);
}

static int	fill_words(char **words, char const *s, char c)
{
	size_t	index;
	size_t	length;

	index = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		length = 0;
		while (s[length] && s[length] != c)
			length++;
		if (length && !add_word(words, &index, s, length))
			return (0);
		s += length;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**words;

	if (!s)
		return (NULL);
	words = ft_calloc(word_count(s, c) + 1, sizeof(char *));
	if (!words)
		return (NULL);
	if (!fill_words(words, s, c))
		return (NULL);
	return (words);
}
