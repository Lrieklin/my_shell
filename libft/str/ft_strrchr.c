/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2000/01/01 20:20:20 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:48:01 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <libft.h>

// Like strchr, but start searching from the end of `s`.
char	*ft_strrchr(const char *s, char c)
{
	const char	*p;

	p = s;
	while (*p)
		p++;
	while (*p != c && p != s)
		p--;
	if (*p == c)
		return ((char *) p);
	else
		return (NULL);
}
