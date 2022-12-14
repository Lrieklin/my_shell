/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 11:44:58 by psharen           #+#    #+#             */
/*   Updated: 2022/10/19 22:53:33 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <get_next_line.h>
#include <fcntl.h>
#include <unistd.h>

#include <minishell.h>

char	*get_heredoc_line(void)
{
	ft_putstr(HEREDOC);
	return (get_next_line(STDIN_FILENO));
}

// Currently weird behavior with `ctrl + D` signals.
void	process_heredoc(int fd, char *eof)
{
	char	*line;
	
	line = get_heredoc_line();
	while (line && !ft_starts_with(eof, line) && line[ft_strlen(eof)] != '\0')
	{
		write(fd, line, ft_strlen(line));
		free(line);
		line = get_heredoc_line();
		if (line == NULL)
			printf("  \b\b");
	}
	free(line);
	close(fd);
}

// UNLIKE Bash, doesn't process all heredocs first. All inputs are processed one
// after another. I think it's more sane to do so. The end result is the same as
// in Bash anyway.
// TODO break down into functions.
bool	process_redirects(t_cmd *cmd)
{
	// printf("process_redirects - start, cmd\n");
	
	t_redirect	*redir;
	int			fd;
	int			heredoc[2];

	heredoc[0] = 0;
	heredoc[1] = 0;

	while (cmd->redirects)
	{
		redir = cmd->redirects->data;
		if (redir->type == T_REDIR_IN)
		{
			// If we had heredoc previously, close its pipe read end. There's
			// probably a better way to manage this, but here we are.
			my_close(&heredoc[0]);
			fd = my_open(redir->name, O_RDONLY, 0);
			if (fd == -1)
				return (false);
			cmd->in_fd = fd;
		}
		else if (redir->type == T_REDIR_OUT)
		{
			fd = my_open(redir->name, O_RDWR | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				return (false);
			cmd->out_fd = fd;
		}
		else if (redir->type == T_REDIR_OUT_APPEND)
		{
			fd = my_open(redir->name, O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
				return (false);
			cmd->out_fd = fd;
		}
		else if (redir->type == T_HEREDOC)
		{
			close_pipe(heredoc);
			if (pipe(heredoc) == -1)
				return perror_and_false("pipe");
			process_heredoc(heredoc[1], redir->name);
			cmd->in_fd = heredoc[0];
		}
		cmd->redirects = cmd->redirects->next;
	}
	return (true);
}
