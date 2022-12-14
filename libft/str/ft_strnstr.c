/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/08/19 15:46:58 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

static int	ft_compare(const char *str, const char *to_find)
{
	while (*str && *to_find)
	{
		if (*str != *to_find)
			return (0);
		str++;
		to_find++;
	}
	return (*to_find == '\0');
}

// Search for `little` substring of `big`, but take only first `n` chars of
// `big`. If `n` is greater than `big` length, then use the whole string.
char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	little_len;

	if (*little == '\0')
		return ((char *) big);
	if (n == 0)
		return (NULL);
	little_len = ft_strlen(little);
	while (*big && n > little_len - 1)
	{
		if (ft_compare(big, little))
			return ((char *) big);
		big++;
		n--;
	}
	return (NULL);
}
