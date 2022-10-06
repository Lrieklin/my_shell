// Not implemented

// I think each builtin should be called as a child process.

#include "minishell.h"
#include <stdio.h>

int	ft_echo(t_cmd *cmd)
{
	int	i;
	int	fl;

	fl = 1;
	i = 0;
	if (cmd->args->next->data && !ft_strcmp(cmd->args->next->data, "-n"))
	{
        printf("hello\n");
		cmd->args->next = cmd->args->next->next;
		fl = 0;

	}
	while (cmd->args->next != NULL)
	{
		printf("%s", (char *)cmd->args->next->data);
        cmd->args->next = cmd->args->next->next;
		if (cmd->args->next)
			printf(" ");
	}
	if (fl)
		printf("\n");
	return (0);
}