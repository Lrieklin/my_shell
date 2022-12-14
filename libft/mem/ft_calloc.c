/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:36:36 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	void			*r;
	size_t			n;

	r = malloc(count * size);
	if (!r)
		return (NULL);
	p = r;
	while (count)
	{
		n = size;
		while (n)
		{
			*p = '\0';
			p++;
			n--;
		}
		count--;
	}
	return (r);
}
