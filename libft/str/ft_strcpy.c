/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:27:02 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 22:27:07 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//		
void	ft_strcpy(char *from, char *to)
{
	size_t	i;

	i = 0;
	while (from[i] != '\0')
	{
		to[i] = from[i];
		i += 1;
	}
	to[i] = '\0';
}