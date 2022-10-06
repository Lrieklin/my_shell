/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_replace.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:34:28 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 21:34:35 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

//	
int	ft_strings_replace(char **strings, char *string, int index)
{
	int	count;
	int	i;

	count = ft_strings_count(strings);
	if (index < 0 || index >= count)
		return (-1);
	i = 0;
	while (i < count)
	{
		if (i == index)
		{
			free(strings[i]);
			strings[i] = string;
			return (i);
		}
		i += 1;
	}
	return (-1);
}