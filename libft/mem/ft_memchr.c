/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:48:20 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

// Search for first `n` bytes for byte `c` in `s`
void	*ft_memchr(const void *s, char c, size_t n)
{
	const unsigned char	*p;

	p = s;
	if (n == 0)
		return (NULL);
	while (*p != c && n - 1)
	{
		p++;
		n--;
	}
	if (*p != c)
		return (NULL);
	else
		return ((void *) p);
}
