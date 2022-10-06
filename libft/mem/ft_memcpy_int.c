/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy_int.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:36:45 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

// Should be faster than ft_memcpy? I don't really know. Maybe it makes more
// sense to use 64 bits instead (unsigned long). See:
// https://stackoverflow.com/questions/17591624
void	*ft_memcpy_int(void *dest, const void *src, size_t n)
{
	unsigned int	*d;
	unsigned int	*s;

	if (!dest && !src)
		return (NULL);
	else if (dest != src)
	{
		d = dest;
		s = (unsigned int *)src;
		while (n)
		{
			*d = *s;
			d++;
			s++;
			n -= 4;
		}
	}
	return (dest);
}
