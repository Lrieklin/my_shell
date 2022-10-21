/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 01:37:20 by psharen           #+#    #+#             */
/*   Updated: 2022/10/03 20:29:41 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>
#include <unistd.h>

void	fail(const char *msg)
{
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(exit_code);
}

void	epic_error(const char *shell, const char *exec_name, const char *msg)
{
	if (shell)
	{
		ft_putstr_fd(shell, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	if (exec_name)
	{
		ft_putstr_fd(exec_name, STDERR_FILENO);
		ft_putstr_fd(": ", STDERR_FILENO);
	}
	ft_putstr_fd(msg, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
}

void	epic_fail(const char *shell, const char *exec_name, const char *msg)
{
	printf("exit code in epic fail: %d\n", exit_code);
	epic_error(shell, exec_name, msg);
	exit(exit_code);
}

bool	perror_and_false(const char *exec_name)
{
	perror(exec_name);
	return (false);
}

// TODO maybe not needed?
void	*clear_data_and_abort(t_list **lst_to_clear)
{
	ft_lstclear(lst_to_clear, free);
	return (NULL);
}
