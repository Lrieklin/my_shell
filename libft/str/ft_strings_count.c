/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_count.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:00:47 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 22:00:53 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//		
size_t	ft_strings_count(char **strings)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
		i += 1;
	return (i);
}