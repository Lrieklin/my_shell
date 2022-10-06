/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_starts_with.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 09:16:13 by psharen           #+#    #+#             */
/*   Updated: 2022/09/02 13:37:09 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include <libft.h>

bool	ft_starts_with(const char *start, const char *s)
{
	while (*start && *s && *start == *s)
	{
		start++;
		s++;
	}
	return (!*start);
}
