/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:32:47 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/03 21:19:29 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int count_size(char **str)
{
    int size = 0;
    while (str[size] != NULL)
    {
        size++;
    }
    return (size);
}

char **copy_env(char **env, int add_qty)
{
    int size = count_size(env) + add_qty;
    char **temp = malloc(sizeof(char*) * (size + 1));
    int i = 0;
    while (i < size - add_qty)
    {
        temp[i] = ft_strdup(env[i]);
        i++;
    }
    temp[size] = NULL;
    return (temp);
}

void free_temp(char **temp)
{
    int size = count_size(temp);
    int i = 0;
    while(i < size)
    {
        free(temp[i]);
        i++;
    }
    free(temp);
}

char **sort_env(char **env)
{
    char **result = copy_env(env, 0);
    int i = 0;
    while (result[i + 1])
    {
        if (ft_strcmp(result[i], result[i + 1]) > 0)
        {
            char *temp = result[i];
            result[i] = result[i + 1];
            result[i + 1] = temp;
            i = -1;
        }
        i++;
    }
    result[i + 1] = NULL;
    return (result); 
}

int	if_without_arg(t_state *state)
{
	char **tmp;

	tmp = sort_env(state->envp);
    int i = 0;
    int size = count_size(tmp);
	while (i < size)
	{
		printf("declare -x %s\n", tmp[i]);
        i++;
	}
    free_temp(tmp);
	return (0);
}

bool    check_var(char *var)
{
    return (ft_isalpha(var[0]) || var[0] == '_');
}

void	builtin_export(t_cmd *cmd, t_state *state)
{
	state->last_exit_code = 0;
	if (!cmd->args->next)
    	if_without_arg(state);
		// return (if_without_arg(data->envp, data));
    else if (check_var(cmd->args->data))
    {
        int list_size = ft_lstsize(cmd->args) - 1;
        char **temp = copy_env(state->envp, list_size);
        t_list *temp_list = cmd->args->next;
        int i = count_size(state->envp);
        int final_size = list_size + i;
        while (i < final_size)
        {
            temp[i] = ft_strdup(temp_list->data);
            i++;
            temp_list = temp_list->next;
        }                
        char **old_env = state->envp;
        state->envp = temp;
        free_temp(old_env);
    }
    else
    {
        printf("%s: export: `%s': not a valid identifier\n", SHELL_NAME, cmd->args->data);
    }
	// return (data->errnum);
}

