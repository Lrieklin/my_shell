/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:02:59 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/02 21:03:43 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	*second_wrong(char *line)
{
	if (line[1] && line[0] == '>' && line[1] == '>')
		return (">>");
	else if (line[1] && line[0] == '<' && line[1] == '<')
		return ("<<");
	else if (line[0] == '>')
		return (">");
	else if (line[0] == '<')
		return ("<");
	else
		return (NULL);
}

char	*wrong_redirects(char *line)
{
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '<' || line[i] == '>')
		{
			i++;
			if (line[i] == '<' || line[i] == '>')
				i++;
			while (line[i] == ' ')
				i++;
			if (line[i] == '<' || line[i] == '>')
				return (second_wrong(&line[i]));
		}
		i++;
	}
	return (NULL);
}

int	empty_redirect(char *line)
{
	int	i;

	i = ft_strlen(line) - 1;
	while (line[i] && line[i] == ' ')
		i--;
	if (line[i] == '<' || line[i] == '>')
		return (1);
	return (0);
}