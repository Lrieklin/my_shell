/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:37:43 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	ft_in(const char *set, char c)
{
	if (!c)
		return (0);
	while (*set && *set != c)
		set++;
	return (*set == c);
}

static char	*ft_strndup_simple(const char *src, size_t len)
{
	char	*result;
	char	*p;

	result = malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	p = result;
	while (len)
	{
		*p = *src;
		p++;
		src++;
		len--;
	}
	*p = '\0';
	return (result);
}

// Trim `s1`, but instead of space chars use chars from `set`.
char	*ft_strtrim(const char *s1, const char *set)
{
	const char	*start;

	while (*s1 && ft_in(set, *s1))
		s1++;
	if (*s1 == '\0')
		return (ft_strndup_simple("", 0));
	start = s1;
	while (*s1)
		s1++;
	while (ft_in(set, s1[-1]) && s1 > start)
		s1--;
	return (ft_strndup_simple(start, s1 - start));
}
