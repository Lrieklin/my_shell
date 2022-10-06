/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psharen <psharen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 12:07:45 by psharen           #+#    #+#             */
/*   Updated: 2022/10/07 00:50:32 by psharen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#include <minishell.h>

void	print_pipeline(t_list *lst);

void	run_tty(t_state *state)
{
	char	*line;

	// Disable readline signal handlers. Not sure if it's necessary.
	signal(SIGINT, &sig_handler_parent);
	signal(SIGQUIT, SIG_IGN);
	
	rl_catch_signals = 0;
	line = readline(PROMPT);
	while (line != NULL)
	{
		if (strlen(line) > 0)
			add_history(line);

		// TODO should be a builtin
		// if (is_help(line))
		// {
		// 	printf(HELP);
		// 	free(line);
		// 	continue;
		// }
		int counter = 0;
		if (check_syntax(line, state) == 0)
		{
			parse_line(&line, state, &counter);
			t_list *pipeline = parse(line);

			#ifdef DEBUG_PIPELINE
			print_pipeline(pipeline);
			#endif

			exec_pipeline(pipeline, state);
			free(line);
			ft_lstclear(&pipeline, free_cmd_data);
		}
		line = readline(PROMPT);
	}
	if (line == NULL)
	{
		printf("\033[1Aʕ•ᴥ•ʔ ➜ exit\n");
		state->last_exit_code = 0;
		exit(EXIT_SUCCESS);
	}
}

void	run_non_tty(t_state *state)
{
	puts("Non-tty mode is not implemented!");
	exit(EXIT_FAILURE);
}
