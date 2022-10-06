/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 05:19:12 by psharen           #+#    #+#             */
/*   Updated: 2022/08/19 15:48:33 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdbool.h>
#include <libft.h>

static size_t	ft_count_words(const char *s, const char *spaces)
{
	size_t	words;
	bool	in_word;

	if (*spaces == '\0')
		return (*s != '\0');
	words = 0;
	in_word = 0;
	while (*s)
	{
		if (!in_word && !ft_strchr(spaces, *s))
		{
			in_word = true;
			words++;
		}
		else if (in_word && ft_strchr(spaces, *s))
			in_word = false;
		s++;
	}
	return (words);
}

// absolutely wicked. moves *s, puts a word in *p.
static void	ft_put_word(char **p, char **s, const char *spaces)
{
	char	*word_start;
	size_t	word_len;

	while (ft_strchr(spaces, **s))
		(*s)++;
	word_start = *s;
	while (**s && !ft_strchr(spaces, **s))
		(*s)++;
	word_len = *s - word_start;
	*p = malloc(sizeof(char) * (word_len + 1));
	if (!*p)
		return ;
	ft_strlcpy(*p, word_start, word_len + 1);
}

static void	ft_free_all(char **words)
{
	char	**p;

	p = words;
	while (*p)
	{
		p++;
		free(p[-1]);
	}
	free(words);
}

// "  hello ,\t world  ", ", \t" --> {"hello", "world", NULL}
// "hello", "\0" --> {"hello", NULL}
char	**ft_split(const char *s, const char *spaces)
{
	size_t	word_count;
	char	**result;
	char	**p;

	word_count = ft_count_words(s, spaces);
	result = ft_calloc(word_count + 1, sizeof(char *));
	if (!result)
		return (NULL);
	p = result;
	while (word_count)
	{
		ft_put_word(p, (char **) &s, spaces);
		if (!*p)
		{
			ft_free_all(result);
			return (NULL);
		}
		word_count--;
		p++;
	}
	return (result);
}
