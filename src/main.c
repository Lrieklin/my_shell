/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:31:24 by psharen           #+#    #+#             */
/*   Updated: 2022/10/15 22:08:43 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

#include <libft.h>
#include <minishell.h>

// TODO remove this?
#include <unistd.h>

// According to POSIX, this is the way you should access environment variables:
// extern char **environ;

void	print_pipeline(t_list *lst)
{
	char *redir_types[] = {"T_REDIR_OUT", "T_REDIR_OUT_APPEND", "T_REDIR_IN", "T_HEREDOC"};

	while (lst)
	{
		t_cmd *cmd = lst->data;
		if (cmd->args)
			printf("cmd:");
		t_list *args = cmd->args;
		while (args)
		{
			printf(" %s", (char *) args->data);
			args = args->next;
		}
		if (cmd->args)
			printf("\n");

		if (cmd->redirects)
			printf("redirects:\n");
		t_list *redirects = cmd->redirects;
		while (redirects)
		{
			t_redirect *r = redirects->data;
			printf("    type: %s, value: %s\n", redir_types[r->type - 2], (char *) r->name);
			redirects = redirects->next;
		}
		if (cmd->redirects)
			printf("\n");
		lst = lst->next;
	}
}

int	main(int argc, const char *argv[], char **environ)
{
	t_state	state;

	exit_code = 1;
	state.envp = copy_string_arr(environ);
	set_value(&state, "TERM_PROGRAM", "MINecraft");
	// print_string_array(state.envp);
	if (isatty(STDIN_FILENO))
		run_tty(&state);
	else
		run_non_tty(&state);
	exit(EXIT_SUCCESS);
}
