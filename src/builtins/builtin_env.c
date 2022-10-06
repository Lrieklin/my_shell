/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 22:20:45 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/22 22:24:27 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdio.h>

void buitin_env(t_state *state)
{
    if (ft_strings_print(state->envp) == -1)
    {
        exit(1);
    }
}
