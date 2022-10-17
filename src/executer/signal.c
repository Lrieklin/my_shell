/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/23 02:26:17 by lrieklin          #+#    #+#             */
/*   Updated: 2022/09/25 22:28:31 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	heredoc_sig_int(int sig)
{	
	// printf("!!!\n");
	// write(STDOUT_FILENO, "\b\b  \b\b\n", 7);
	// rl_on_new_line();
	if (sig == SIGINT)
	{
		write(1, "\b\b  \b\b", 6);
		// write(1, "\n( ≖_≖) > ", 15);
		rl_on_new_line();
		rl_replace_line("", 1);
		// rl_redisplay();
		exit(0);
	}
	if (sig == SIGQUIT) {
		printf("SIGQUIT\n");
	}
	
	// if (sig == SIGINT)
	// {
	// 	write(1, "\b\b  \b\b", 6);
	// 	write(1, "\n( ≖_≖) > ", 15);
	// }
	// if (sig == SIGQUIT)
	// {
	// 	write(1, "\b\b  \b\b", 6);
	// }
}

// void	signal_handler(int a, t_state *state)
// {
// 	if (a == SIGINT)
// 	{
// 		printf("\n");
// 		rl_on_new_line();
// 		rl_replace_line("", 0);
// 		rl_redisplay();
// 		state->last_exit_code = 1;
// 	}
// }

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