/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_get_index.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:33:57 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 21:34:05 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//	
int	ft_strings_get_index(char **strings, char *part)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		if (ft_strncmp(strings[i], part, ft_strlen(part)) == 0)
		{	
			return (i);
		}
		i += 1;
	}
	return (-1);
}