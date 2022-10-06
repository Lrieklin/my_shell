/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:00:41 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/02 21:02:44 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	last_pipe(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '|')
		return (1);
	return (0);
}

int	unclosed_quotes(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\'' && quotes1 == 0)
			quotes1++;
		else if (line[i] == '\'')
			quotes1--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

int	unclosed_double_quotes(char *line)
{
	int	i;
	int	quotes1;
	int	quotes2;

	i = 0;
	quotes1 = 0;
	quotes2 = 0;
	while (line[i])
	{
		if (line[i] == '\"' && quotes2 == 0)
			quotes2++;
		else if (line[i] == '\"')
			quotes2--;
		i++;
	}
	if (quotes1 || quotes2)
		return (1);
	return (0);
}

char	*other_syntax_cases(char *line)
{
	if (last_pipe(line))
		return ("minishell: syntax error: unexpected end of file");
	else if (unclosed_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\'\'");
	else if (unclosed_double_quotes(line))
		return ("minishell: unexpected EOF while looking for matching `\"\'");
	else
		return (NULL);
}

void	tabs_to_spaces(char **line)
{
	int	i;

	i = 0;
	while ((*line)[i])
	{
		if ((*line)[i] == '\t' || (*line)[i] == '\n')
			(*line)[i] = ' ';
		i++;
	}
}