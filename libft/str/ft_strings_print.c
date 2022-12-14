/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strings_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:18:30 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 22:20:06 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static size_t	get_lenght(char **strings)
{
	size_t	i;

	i = 0;
	while (*strings != NULL)
	{
		i += ft_strlen(*strings++) + 1;
	}
	return (i);
}

static void	copy_to_string(char **strings, char *string)
{
	while (*strings != NULL)
	{
		ft_strcpy(*strings, string);
		string += ft_strlen(*strings) + 1;
		*(string - 1) = '\n';
		strings++;
	}
}

//	
int	ft_strings_print(char **strings)
{
	char	*string;
	size_t	lenght;

	lenght = get_lenght(strings);
	string = (char *)malloc(lenght * sizeof(char));
	if (string == NULL)
		return (-1);
	copy_to_string(strings, string);
	if (write(1, string, lenght) != (ssize_t)lenght)
	{
		free(string);
		return (-1);
	}
	else
	{
		free(string);
		return (0);
	}
}