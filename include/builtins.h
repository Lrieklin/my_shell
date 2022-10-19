// not implemented yet

#ifndef LOL
# define LOL

#include "minishell.h"

void    builtin_exit(t_cmd *cmd);
int     ft_echo(t_cmd *cmd, t_state *state);
int	builtin_cd(t_state *state, char *new_path);
int    buitin_env(t_state *state);
int     builtin_pwd(t_state *state);
int 	built_unset(t_cmd *cmd, t_state *state);
void	builtin_export(t_cmd *cmd, t_state *state);

#endif
