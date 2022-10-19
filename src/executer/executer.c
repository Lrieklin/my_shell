/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 15:02:07 by psharen           #+#    #+#             */
/*   Updated: 2022/10/16 03:39:32 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

#include <minishell.h>
#include <builtins.h>

static char	**lst_to_string_array(t_list *lst)
{
	char	**arr;
	char	**p;

	arr = malloc(sizeof(*arr) * (ft_lstsize(lst) + 1));
	if (!arr)
	{
		perror("lst_to_string_array()");
		exit(EXIT_FAILURE);
	}
	p = arr;
	while (lst)
	{
		*p = lst->data;
		lst = lst->next;
		p++;
	}
	*p = NULL;
	return (arr);
}

void	exec_cmd(t_cmd *cmd, t_state *state, int l_pipe[], int r_pipe[])
{
	char	*pathname;
	char	*exec_name;

	if (!process_redirects(cmd))
		exit(EXIT_FAILURE);
	
	exec_name = cmd->args[0].data;
	if (!exec_name)
		exit(EXIT_SUCCESS);
	if (is_builtin(cmd, state) == true) 
		return ;
	else if (exec_name[0] == '/')
		pathname = exec_name;
	else
		pathname = get_pathname(my_getenv(state->envp, "PATH"), exec_name);
	if (!pathname)
	{
		exit_code = 127;
		epic_fail(SHELL_NAME, exec_name, "command not found");
	}

	if (cmd->in_fd)
		dup2(cmd->in_fd, STDIN_FILENO);
	if (cmd->out_fd)
		dup2(cmd->out_fd, STDOUT_FILENO);
	close_unused_fds(cmd, l_pipe, r_pipe);

	char **argv = lst_to_string_array(cmd->args);
	execve(pathname, argv, state->envp);
	perror(argv[0]);
	exit(EXIT_FAILURE);
}

void	prepare_cmd(t_cmd *cmd, int l_pipe[], int r_pipe[])
{
	if (l_pipe[0])
		cmd->in_fd = l_pipe[0];
	if (r_pipe[1])
		cmd->out_fd = r_pipe[1];
	// TODO perform variable expasion inside double quotes!
}

bool	try_fork(t_cmd *cmd, t_state *state, int l_pipe[], int r_pipe[])
{
	pid_t	pid;

	pid = 0;
	pid = fork();
	if (pid == 0)
	{
		// printf("child\n");
		signal(SIGINT, &sig_handler_child);
		signal(SIGQUIT, &sig_handler_child);
		// signal(SIGINT, SIG_DFL);
		// signal(SIGQUIT, SIG_DFL);
		prepare_cmd(cmd, l_pipe, r_pipe);
		exec_cmd(cmd, state, l_pipe, r_pipe);
	}
	else if (pid == -1)
	{
		close_pipe(l_pipe);
		close_pipe(r_pipe);
		return (false);
	}
	else if (pid != 0)
	{
		if (l_pipe[0])
		{
			close(l_pipe[0]);
			l_pipe[0] = 0;
		}
		if (r_pipe[1])
		{
			close(r_pipe[1]);
			r_pipe[1] = 0;
		}
		signal(SIGINT, SIG_IGN);
		// signal(SIGQUIT, &sig_handler_child);
	}
	
	return (true);
}

// TODO save last exit code in `$?` variable, probably through `export` bulitin
// @param pipeline - a list of t_cmd's, one or more
// We can't use fcntl() to check if a file descriptor is valid, so I'm using
// 0 to mark invalid ones.

bool is_builtin(t_cmd *cmd, t_state *state)
{
	// call func redirect
	char *name;

	name = cmd->args->data;
	if (ft_strcmp(name, "exit") == 0)
		builtin_exit(cmd);
	if (ft_strcmp(name, "echo") == 0)
		exit_code = ft_echo(cmd, state);
	else if (ft_strcmp(name, "cd") == 0)
		exit_code = builtin_cd(state, ((char *)cmd->args->next->data));
	else if (ft_strcmp(name, "env") == 0)
		exit_code = buitin_env(state);
	else if (ft_strcmp(name, "pwd") == 0)
		exit_code = builtin_pwd(state);
	else if (ft_strcmp(name, "unset") == 0)
		exit_code = built_unset(cmd, state);
	else if (ft_strcmp(name, "export") == 0)
		builtin_export(cmd, state);
	else
		return (false);
	return (true);
}

bool	exec_pipeline(t_list *pipeline, t_state *state)
{
	int		l_pipe[2];
	int		r_pipe[2];
	// pid_t	pid;

	l_pipe[0] = 0;
	l_pipe[1] = 0;
	r_pipe[0] = 0;
	r_pipe[1] = 0;
	if (ft_lstsize(pipeline) == 1 && is_builtin(pipeline->data, state) == true)
		return (true);
	while (pipeline)
	{
		next_pipe(l_pipe, r_pipe);
		if (pipeline->next && pipe(r_pipe) == -1)
			return (perror_and_false("pipe"));
		if (!try_fork(pipeline->data, state, l_pipe, r_pipe))
			return (perror_and_false("fork"));
		pipeline = pipeline->next;
	}
	close_pipe(l_pipe);
	close_pipe(r_pipe);

	int	status;
	// int i = -1;
	
	// while (++i < num)
		waitpid(-1, &status, 0);

	if (WIFEXITED(status))
		exit_code = WEXITSTATUS(status);
	else
		exit_code = status + 128;

	// free(pid);
	

	// pid = wait(NULL);
	// while (pid > 0)
	// {
	// 	// printf("Done with process: %d\n", pid);
	// 	pid = wait(NULL);
	// }
	return (true);
}
