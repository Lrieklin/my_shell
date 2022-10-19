/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 20:58:56 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/16 02:23:42 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

int	wrong_pipes(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == '|')
		return (1);
	while (line[i])
	{
		if (line[i] == '|' || line[i] == '>' || line[i] == '<')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (0);
			if (line[i] == '>' || line[i] == '<')
				i++;
			while (line[i] && !ft_isalnum(line[i]) && line[i] != '|')
				i++;
			if (line[i] == '|')
				return (1);
		}
		i++;
	}
	return (0);
}

int	wrong_semicolon(char *line)
{
	int		i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] == ';')
		return (1);
	while (line[i])
	{
		if (line[i] == ';')
		{
			i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == ';')
				return (1);
		}
		i++;
	}
	return (0);
}

int	double_semicolon(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i + 1] && line[i] == ';' && line[i + 1] == ';')
			return (1);
		i++;
	}
	return (0);
}

char	*unexpected_token(char *line)
{
	if (line[0] == '|' && line[1] == '|')
		return ("||");
	if (wrong_pipes(line))
		return ("|");
	else if (double_semicolon(line))
		return (";;");
	else if (wrong_semicolon(line))
		return (";");
	else if (wrong_redirects(line))
		return (wrong_redirects(line));
	else if (empty_redirect(line))
		return ("newline");
	else
		return (NULL);
}

int	check_syntax(char *line, t_state *state)
{
	if (unexpected_token(line))
	{
		printf("bear shell: syntax error near unexpected token `%s\'\n", \
			unexpected_token(line));
		state->last_exit_code = 258;
		return (1);
	}
	else if (other_syntax_cases(line))
	{
		printf("%s\n", other_syntax_cases(line));
		state->last_exit_code = 258;
		return (1);
	}
	else
		return (0);
}
