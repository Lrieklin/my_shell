/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_unset.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 21:05:38 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/16 03:17:12 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void	remove_r(char **strings, char **new, int index)
{
	int	i;

	i = 0;
	while (strings[i] != NULL)
	{
		if (i == index)
		{
			free(strings[i]);
			strings++;
			if (strings[i] == NULL)
				break ;
		}
		new[i] = strings[i];
		i += 1;
	}
	new[i] = NULL;
}

void	ft_strings_remove_all(char ***strings)
{
	char	**temporary;

	temporary = *strings;
	while (*temporary != NULL)
		free(*temporary++);
	free(*strings);
	*strings = NULL;
}

void	ft_strings_remove(char ***strings, int index)
{
	char	**new;
	size_t	count;

	count = ft_strings_count(*strings);
	if (index < 0 || index >= (int)count)
		return ;
	new = (char **)malloc(count * sizeof(char *));
	if (new == NULL)
	{
		ft_strings_remove_all(strings);
		return ;
	}
	remove_r(*strings, new, index);
	free(*strings);
	*strings = new;
}

void	ft_strings_remove_by_part(char ***strings, char *part)
{
	int	index;

	index = ft_strings_get_index(*strings, part);
	if (index == -1)
		return ;
	ft_strings_remove(strings, index);
}

void	envp_remove(char *variable, t_state *state)
{
	char	*postfix;

	postfix = ft_strjoin(variable, "=");
	if (postfix == NULL)
		exit(EXIT_FAILURE);
	ft_strings_remove_by_part(&state->envp, postfix);
    if (state->envp == NULL)
        exit(EXIT_FAILURE);
	free(postfix);
}

int	built_unset(t_cmd *cmd, t_state *state)
{
    t_list  *list;

    list = cmd->args->next;
    while (list != NULL)
    {
        envp_remove(list->data, state);
        printf("%s\n", (char *)list->data);
        list = list->next;
    }
	return (0);
}
