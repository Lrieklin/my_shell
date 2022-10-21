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

int	exit_code;

// According to POSIX, this is the way you should access environment variables:
// extern char **environ;

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
