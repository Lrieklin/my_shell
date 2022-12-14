/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:00:54 by psharen           #+#    #+#             */
/*   Updated: 2022/10/02 21:07:03 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>

#include <libft.h>
#include <minishell.h>

static t_list *parse_arg(t_scanner *sc)
{
	t_list			*elem;

	if (!expect(sc->token, T_WORD))
		return (NULL);
	elem = ft_lstnew(sc->token->value);
	if (!elem)
		fail("Out of memory!");
	scan_next_token(sc);
	return (elem);
}

// redirect = (">" | "<" | ">>" | "<<") word
static t_list	*parse_redirect(t_scanner *sc)
{
	t_redirect	*redir;
	t_list		*lst_elem;

	if (!expect(sc->token, T_REDIR))
		return (NULL);
	redir = malloc(sizeof(*redir));
	redir->type = sc->token->type;
	scan_next_token(sc);
	if (!expect(sc->token, T_WORD))
	{
		free(redir);
		return (NULL);
	}
	redir->name = sc->token->value;
	lst_elem = ft_lstnew(redir);
	if (!lst_elem)
		fail("Out of memory!");
	scan_next_token(sc);
	return (lst_elem);
}

// ft_lstadd_back without O(n^2) and twice the code complexity.
static void	epic_lstadd_back(t_list *elem, t_list **last_elem, t_list **lst)
{
	if (!*lst)
	{
		*lst = elem;
		*last_elem = elem;
	}
	else
	{
		(*last_elem)->next = elem;
		*last_elem = elem;
	}
}

// Parse and save either a word, or a redirect.
static bool	parse_and_save_cmd_part(t_scanner *sc, t_cmd *cmd)
{
	t_list			*cur_arg;
	t_list			*cur_redir;
	static t_list	*last_arg;
	static t_list	*last_redir;

	if (sc->token->type == T_WORD)
	{
		cur_arg = parse_arg(sc);
		if (!cur_arg)
			return (false);
		epic_lstadd_back(cur_arg, &last_arg, &cmd->args);
	}
	else
	{
		cur_redir = parse_redirect(sc);
		if (!cur_redir)
			return (false);
		epic_lstadd_back(cur_redir, &last_redir, &cmd->redirects);
	}
	return (true);
}

// cmd = word | redirect {word | redirect}
// (yes, "> wat" is a valid command in Bash)
t_list	*parse_command(t_scanner *sc)
{
	t_cmd	*cmd;
	t_list	*lst_elem;

	cmd = ft_calloc(1, sizeof(*cmd));
	lst_elem = ft_lstnew(cmd);
	if (!cmd || !lst_elem)
		fail("Out of memory!");
	lst_elem->data = cmd;
	if (!parse_and_save_cmd_part(sc, cmd))
	{
		ft_lstclear(&lst_elem, free_cmd_data);
		return (NULL);
	}
	while (sc->token->type == T_WORD || is_redirect(sc->token->type)) {
		if (!parse_and_save_cmd_part(sc, cmd))
		{
			ft_lstclear(&lst_elem, free_cmd_data);
			return (NULL);
		}
	}
	return (lst_elem);
}
