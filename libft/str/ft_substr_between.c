/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_between.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 08:53:52 by psharen           #+#    #+#             */
/*   Updated: 2022/08/22 09:28:43 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// Chair pointed by *end is NOT included.
char	*ft_substr_between(const char *start, const char *end)
{
	return (ft_substr(start, 0, end - start));
}
