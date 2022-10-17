/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 20:40:23 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/02 20:55:53 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	remove_quotes(char *line, int begin, int *i)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(line);
	while (begin + j < *i - 1)
	{
		line[begin + j] = line[begin + j + 1];
		j++;
	}
	while (begin + j < len - 2)
	{
		line[begin + j] = line[begin + j + 2];
		j++;
	}
	while (begin + j < len)
	{
		line[begin + j] = '\0';
		j++;
	}
}

char	*single_quotes(char *line, int *i)
{
	int		begin;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\'')
	{
		if (line[*i] == ' ')
			line[*i] = '\a';
		(*i)++;
	}
	remove_quotes(line, begin, i);
	(*i) -= 2;
	return (line);
}

char	*double_quotes(char *line, int *i, char **envp)
{
	int		begin;

	begin = *i;
	(*i)++;
	while (line[*i] && line[*i + 1] && line[*i] != '\"')
	{
		if (line[*i] == '$' && (line[*i + 1] == '_' || \
			ft_isalpha(line[*i + 1])))
		{
			line = env_replace(line, i, envp);
			(*i)--;
		}
		if (line[*i] == ' ')
			line[*i] = '\a';
		(*i)++;
	}
	remove_quotes(line, begin, i);
	(*i) -= 2;
	return (line);
}

void	parse_line(char **line, t_state *state, int *i)
{
	char *temp = *line;
    while ((*line)[*i] && (*line)[*i] != '|')
	{		
		while ((*line)[*i] == ' ')
			(*i)++;
		if ((*line)[*i] == '\"')
			(*line) = double_quotes((*line), i, state->envp);
		else if ((*line)[*i] == '\'')
			(*line) = single_quotes((*line), i);
		if ((*line)[*i] == '$' && ((*line)[*i + 1] == '_' || \
			ft_isalpha((*line)[*i + 1])))
			(*line) = env_replace((*line), i, state->envp);
		if ((*line)[*i] == '$' && (*line)[*i + 1] == '?')
			(*line) = exit_code_replace((*line), state, i);
		if ((*line)[*i] != '|')
			(*i)++;
	}
    line = &temp;
}