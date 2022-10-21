/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/24 08:52:25 by psharen           #+#    #+#             */
/*   Updated: 2022/10/15 22:01:23 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <minishell.h>

// Same as strchr, but:
// - returns booleans
// - if c is '\0', returns false
bool	in(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return (true);
		s++;
	}
	return (false);
}

// Yes. I need this.
bool	strequal(const char *s1, const char *s2)
{
	return (ft_strcmp(s1, s2) == 0);
}

void	free_redirect_data(void *redirect)
{
	t_redirect	*r;

	r = redirect;
	free(r->name);
	free(r);
}

void	free_cmd_data(void *cmd)
{
	t_cmd	*c;

	c = cmd;
	ft_lstclear(&c->args, free);
	ft_lstclear(&c->redirects, free_redirect_data);
	free(c);
}

// Just trim 'expr' and compare it to "help". Don't want to use ft_strtrim,
// because it uses malloc.
// TODO make this a builtin.
bool	is_help(const char *expr)
{
	while (in(SPACE_CHARS, *expr))
		expr++;
	if (ft_starts_with("help", expr) && (expr[4] == '\0' || in(SPACE_CHARS, expr[4])))
		return (1);
	else if (ft_starts_with("exit", expr) && (expr[4] == '\0' || in(SPACE_CHARS, expr[4])))
	{
		exit(EXIT_FAILURE);
	}
	return (0);
}

char	*my_getenv(char *envp[], char *var)
{
	while (*envp)
	{
		if (ft_starts_with(var, *envp) && (*envp)[ft_strlen(var)] == '=')
			return (*envp + ft_strlen(var) + 1);
		envp++;
	}
	return (NULL);
}

int	my_open(const char *file, int flags, mode_t mode)
{
	int	fd;

	if (mode == 0)
		fd = open(file, flags);
	else
		fd = open(file, flags, mode);
	if (fd == -1)
		epic_error(SHELL_NAME, file, strerror(errno));
	return (fd);
}

void	my_close(int *fd)
{
	if (fd && *fd)
		close(*fd);
	*fd = 0;
}

char	**copy_string_arr(char *arr[])
{
	size_t	size;
	size_t	i;
	char	**copy;

	if (!arr)
		return (NULL);
	size = 0;
	while (arr[size])
		size++;
	copy = malloc((size + 1) * sizeof(char *));
	if (!copy)
		fail("Out of memory!");
	i = 0;
	while (arr[i])
	{
		copy[i] = ft_strdup(arr[i]);
		if (!copy[i])
			fail("Out of memory!");
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

// TODO remove this
void	print_string_array(const char *arr[])
{
	if (!arr)
		return ;
	while (*arr)
	{
		printf("%s\n", *arr);
		arr++;
	}
}

void	set_value(t_state *env, char *key, char *value)
{
	char *temp_str;
	char *ready_str;

	temp_str = ft_strjoin(key, "=");
	if (!temp_str)
		exit(EXIT_FAILURE);
	ready_str = ft_strjoin(temp_str, value);
	if (!ready_str)
		exit(EXIT_FAILURE);
	if (ft_strings_replace_by_part(env->envp, ready_str, temp_str) == -1)
	{
		free(ready_str);
	}
	free(temp_str);
}

// void	print_pipeline(t_list *lst)
// {
// 	char *redir_types[] = {"T_REDIR_OUT", "T_REDIR_OUT_APPEND", "T_REDIR_IN", "T_HEREDOC"};

// 	while (lst)
// 	{
// 		t_cmd *cmd = lst->data;
// 		if (cmd->args)
// 			printf("cmd:");
// 		t_list *args = cmd->args;
// 		while (args)
// 		{
// 			printf(" %s", (char *) args->data);
// 			args = args->next;
// 		}
// 		if (cmd->args)
// 			printf("\n");

// 		if (cmd->redirects)
// 			printf("redirects:\n");
// 		t_list *redirects = cmd->redirects;
// 		while (redirects)
// 		{
// 			t_redirect *r = redirects->data;
// 			printf("    type: %s, value: %s\n", redir_types[r->type - 2], (char *) r->name);
// 			redirects = redirects->next;
// 		}
// 		if (cmd->redirects)
// 			printf("\n");
// 		lst = lst->next;
// 	}
// }
