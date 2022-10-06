// Not implemented

// I think each builtin should be called as a child process.

#include "minishell.h"

void	check_(char *code)
{
	int	i;

	i = 0;
	if (code[i] == '-')
	{
		i += 1;
	}
	if (code[i] == '\0')
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: -: numeric argument required\n", 46);
		exit(255);
	}
	while (ft_isdigit(code[i]) == true)
	{
		i += 1;
	}
	if (code[i] != '\0')
	{
		write(2, "exit\n", 5);
		write(2, "minishell: exit: ", 17);
		write(2, code, ft_strlen(code));
		write(2, ": numeric argument required\n", 28);
		exit(255);
	}
}

char	**ft_list_to_strings(t_list *head)
{
	char	**strings;
	int		i;

	strings = (char **)malloc(sizeof(char *) * (ft_lstsize(head) + 1));
	if (strings == NULL)
		return (NULL);
	i = 0;
	while (head != NULL)
	{
		strings[i] = head->data;
		head = head->next;
		i += 1;
	}
	strings[i] = NULL;
	return (strings);
}

void	builtin_exit(t_cmd *cmd)
{
    char            **code;
	unsigned char	_code;

    code = ft_list_to_strings(cmd->args);
    if (code == NULL)
    {
        exit(1);
    }
	if (code[1] == NULL)
	{
		write(2, "exit\n", 5);
		exit(0);
	}
	check_(code[1]);
	_code = ft_atoi(code[1]);
	if (code[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		return ;
	}
	write(1, "exit\n", 5);
	exit(_code);
}
