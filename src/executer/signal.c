/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:26:17 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/19 23:01:45 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include "minishell.h"

#include "minishell.h"

void	sig_handler_child(int sig_num)
{
	if (sig_num == SIGINT)
	{
		write(2, "\n", 1);
		rl_on_new_line();
	}
	else if (sig_num == SIGQUIT)
	{
		write(2, "Quit: 3\n", 8);
		rl_on_new_line();
	}
}

void	sig_handler_parent(int sig_num)
{	
	if (sig_num == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		write(1, "  \b\b\n", 5);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig_num == SIGQUIT)
	{
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		write(1, "  \b\b", 4);
	}
}


int	extract_g_exit_status(int status, t_state *state)
{
	if (state->last_exit_code)
		return (state->last_exit_code);
	if (WIFEXITED(status))
	{
		if (!status)
			return (0);
		if (WEXITSTATUS(status) == 255)
			return (127);
	}
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 2)
			return (130);
		else if (WTERMSIG(status) == 3)
			return (131);
		return (WEXITSTATUS(status));
	}
	return (WEXITSTATUS(status));
}