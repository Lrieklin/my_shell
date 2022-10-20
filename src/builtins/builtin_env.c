/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:20:45 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/16 03:16:33 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

int buitin_env(t_state *state)
{
    if (ft_strings_print(state->envp) == -1)
    {
        exit(1);
    }
    return (0);
}
