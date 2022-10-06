/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:59:34 by psharen           #+#    #+#             */
/*   Updated: 2022/10/03 20:22:53 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define DEBUG_PIPELINE

# include <stdbool.h>
# include <libft.h>

# include <scanner.h>
# include <constants.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

// # include <builtins.h>

int exit_code;

// NOTICE
// If you change t_redirect or t_cmd, don't forget to update their free()
// functions
typedef struct s_redirect {
	t_token_type	type;
	char			*name;
}	t_redirect;

typedef struct s_cmd {
	t_list	*args;      // a list of strings (includes command name)
	t_list	*redirects; // a list of t_redirect's
	int		in_fd;
	int		out_fd;
}	t_cmd;

typedef struct s_state {
	int		last_exit_code;
	char	**envp;
}	t_state;

// parser
void	parse_line(char **line, t_state *state, int *i);
char	*env_replace(char *line, int *i, char **envp);
char	*exit_code_replace(char *line, t_state *state, int *i);
t_list	*parse(char *expr);
int		check_syntax(char *line, t_state *state);
char	*other_syntax_cases(char *line);
char	*wrong_redirects(char *line);
int		empty_redirect(char *line);

bool	is_redirect(t_token_type t);
bool	expect(t_token *token, t_token_type expected_type);
t_list	*parse_command(t_scanner *sc);
t_list	*parse_pipeline(t_scanner *sc);

// run
void	run_tty(t_state *state);
void	run_non_tty(t_state *state);

// executer
bool	exec_pipeline(t_list *pipeline, t_state *state);

// exec_helpers
char	*get_pathname(char *PATH, char *exec_name);
void	close_pipe(int p[]);
void	close_unused_fds(t_cmd *cmd, int l_pipe[], int r_pipe[]);
void	next_pipe(int l_pipe[], int r_pipe[]);

// redirects
bool	process_redirects(t_cmd *cmd);

// errors
void	fail(const char *msg);
void	epic_error(const char *shell, const char *exec_name, const char *msg);
void	epic_fail(const char *shell, const char *exec_name, const char *msg);
bool	perror_and_false(const char *exec_name);
// void	*clear_data_and_abort(t_list **lst_to_clear);

// utils
bool	in(const char *s, char c);
bool	strequal(const char *s1, const char *s2);
void	free_redirect_data(void *redirect);
void	free_cmd_data(void *cmd);
bool	is_help(const char *expr);
char	*my_getenv(char *envp[], char *var);
int		my_open(const char *file, int flags, mode_t mode);
void	my_close(int *fd);
char	**copy_string_arr(char *arr[]);

void	print_string_array(const char *arr[]);
void	set_value(t_state *env, char *key, char *value);

// signals
void	sig_handler_parent(int sig_num);
void	sig_handler_child(int sig_num);
void	heredoc_sig_int(int sig);
bool	is_builtin(t_cmd *cmd, t_state *state);

#endif
