/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_replace_by_part.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:34:28 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 21:50:25 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int	ft_strings_replace_by_part(char **strings, char *string, char *part)
{
	int	index;

	index = ft_strings_get_index(strings, part);
	return (ft_strings_replace(strings, string, index));
}