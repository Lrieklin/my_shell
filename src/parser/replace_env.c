/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:53:47 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/19 22:42:09 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static char	*replace_str(char *line, char *old, char *new, int start)
{
	int		i;
	int		j;
	int		k;
	char	*result;
	int		res_len;

	i = 0;
	j = 0;
	k = 0;
	res_len = ft_strlen(line) - ft_strlen(old) + ft_strlen(new);
	result = malloc(sizeof(*line) * res_len);
	while (i < res_len && i < start)
	{
		result[i] = line[i];
		i++;
	}
	k = i + ft_strlen(old) + 1;
	while (new[j])
		result[i++] = new[j++];
	while (line[k])
		result[i++] = line[k++];
	result[i] = '\0';
	return (result);
}

char	*exit_code_replace(char *line, t_state *state, int *i)
{
	char	*exit_code_str;

	exit_code_str = ft_itoa(exit_code);
	line = replace_str(line, "?", exit_code_str, *i);
	return (line);
}

char	*env_replace(char *line, int *i, char **envp)
{
	int		begin;
	char	*env_key;
	char	*env_value;

	begin = *i;
	env_value = ft_strdup("");
	(*i)++;
	while (line[*i] && (line[*i] == '_' || ft_isalnum(line[*i])))
		(*i)++;
	env_key = ft_substr(line, begin + 1, *i - begin - 1);
	char **temp = envp;
    while (*temp)
    {
        int key_len = ft_strlen(env_key);
		if (ft_strncmp(env_key, *temp, ft_strlen(env_key)) == 0 && (*temp)[key_len] == '=')
        {
            env_value = ft_substr(*temp, ft_strlen(env_key) + 1, ft_strlen(*temp) - ft_strlen(env_key) - 1);
        }
        temp++;
    }
	line = replace_str(line, env_key, env_value, begin);
	*i = begin + ft_strlen(env_value) - 1;
	free(env_key);
	return (line);
}
