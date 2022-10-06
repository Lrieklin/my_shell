/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 21:13:51 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/03 21:32:27 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

// char    *ft_strcat(char *str1, char *str2)
// {
//     char    *result;
//     int i = 0;
//     int j = 0;
    
//     result = malloc(sizeof(char) * (ft_strlen(str1) + ft_strlen(str2) + 1));
//     while (i < ft_strlen(str1))
//     {
//         result[i] = str1[i];
//         i++;
//     }
//     while (i < ft_strlen(str2))
//     {
//         result[i] = str1[j];
//         i++;
//         j++;
//     }
//     result[i] = '\0';
//     return (result);
// }