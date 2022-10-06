/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/08/19 15:46:54 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

// Concatenate `src` to `dest`, given that `dst` length is `dstsize`. Truncate
// `src` otherwise. `dst` remains null-terminated.
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		n;

	n = dstsize;
	while (n && *dst)
	{
		dst++;
		n--;
	}
	if (n > 0)
	{
		while (n - 1 && *src)
		{
			*dst = *src;
			dst++;
			src++;
			n--;
		}
		*dst = '\0';
	}
	return (ft_strlen(src) + dstsize - n);
}
