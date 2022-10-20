/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrieklin <lrieklin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 21:08:28 by lrieklin          #+#    #+#             */
/*   Updated: 2022/10/16 03:30:55 by lrieklin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>
#include <stdio.h>

void	ft_strings_remove_all(char ***strings);

int	ft_is_str_equal(char *str1, char *str2)
{
	int	result;
	
	if (str1 == NULL || str2 == NULL)
		return (0);
	result = ft_strcmp(str1, str2);
	if (result == 0)
		return (1);
	return (0);
}

void	envp_replace(t_state *state, char *variable, char *value)
{
	char	*postfix;
	char	*data;

	postfix = ft_strjoin(variable, "=");
	if (postfix == NULL)
	{
		perror(NULL);
		exit(1);
	}
	data = ft_strjoin(postfix, value);
	if (data == NULL)
	{
		perror(NULL);
		exit(1);
	}
	if (ft_strings_replace_by_part(state->envp, data, postfix) == -1)
	{
		free(data);
	}
	free(postfix);
}



static void	append(char **strings, char **new, char *string)
{
	size_t	i;

	i = 0;
	while (strings[i] != NULL)
	{
		new[i] = strings[i];
		i += 1;
	}
	new[i] = string;
	new[i + 1] = NULL;
}

//		
void	ft_strings_append(char ***strings, char *string)
{
	char	**new;

	new = (char **)malloc((ft_strings_count(*strings) + 2) * sizeof(char *));
	if (new == NULL)
	{
		ft_strings_remove_all(strings);
		return ;
	}
	append(*strings, new, string);
	free(*strings);
	*strings = new;
}

char	*ft_strings_get_string(char **strings, char *part)
{
	while (*strings != NULL)
	{
		if (ft_strncmp(*strings, part, ft_strlen(part)) == 0)
		{	
			return (*strings);
		}
		strings++;
	}
	return (NULL);
}

char	*envp_get_value(char **envp, char *variable)
{
	char	*postfix;
	char	*string;

	postfix = ft_strjoin(variable, "=");
	if (postfix == NULL)
	{
		perror(NULL);
		exit(1);
	}
	string = ft_strings_get_string(envp, postfix);
	free(postfix);
	if (string == NULL)
	{
		return (NULL);
	}
	else
	{
		string += ft_strlen(variable) + 1;
		return (string);
	}
}

void	envp_append(t_state *state, char *variable, char *value)
{
	char	*postfix;
	char	*data;

	postfix = ft_strjoin(variable, "=");
	if (postfix == NULL)
	{
		perror(NULL);
		exit(1);
	}
	data = ft_strjoin(postfix, value);
	if (data == NULL)
	{
		perror(NULL);
		exit(1);
	}
	free(postfix);
	ft_strings_append(&state->envp, data);
	if (state->envp == NULL)
		exit(1);
}

void ms_error(char *func_name, char *str_error, int errn)
{
	errno = errn;
	if (str_error)
	{
		ft_putstr_fd("bear shell: ", 2);
		ft_putstr_fd(func_name, 2);
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str_error, 2);
		ft_putstr_fd("\n", 2);
		return ;
	}	
	ft_putstr_fd("bear shell: ", 2);
	perror(func_name);
}

int	ms_error_free_return(char *msg, char *to_free)
{
	if (to_free)
		free(to_free);
	ms_error(msg, NULL, errno);
	return (errno);
}

static int	cd_error(char *error, int retrn)
{
	ms_error("cd", error, 1);
	return (retrn);
}
/* 
Try to change pwd, return errno from chdir
 */
static int update_pwd(t_state *state, char *new_cwd)
{
	int		chdir_result;
	char	*cwd;

	chdir_result = chdir(new_cwd);
	if (chdir_result != 0)
	{
		ms_error("cd", NULL, errno);
		return (0);
	}
	else
	{
		cwd = getcwd(NULL, 10000);
		if (! cwd)
		{
			ms_error("cd -> update_pwd", NULL, errno);
			return (errno);
		}
		if (envp_get_value(state->envp, "OLDPWD") == NULL)
			envp_append(state, "OLDPWD", envp_get_value(state->envp, "PWD"));
		else
			envp_replace(state, "OLDPWD", envp_get_value(state->envp, "PWD"));
		envp_replace(state, "PWD", cwd);
		free(cwd);
	}
	return (errno);
}

/*
Return 1 if cwd changed successfully
Return 0 if error has occured
ERRNO = 1 if error has occured
TODO	~
TODO	-
Change current ENVP by "void	envp_replace(char *variable, char *value)"
*/

int	builtin_cd(t_state *state, char *new_path)
{
	char	*home_dir;
	char	*old_pwd;
	int		errn;

	if (new_path == NULL || new_path[0] == 0 || ft_is_str_equal(new_path, "~"))
	{
		home_dir = envp_get_value(state->envp, "HOME");
		if (home_dir == NULL)
			return(cd_error("HOME not set", 0));
		errn = update_pwd(state, home_dir);
		return(! errn);
	}
	else if (ft_is_str_equal(new_path, "-"))
	{
		old_pwd = envp_get_value(state->envp, "OLDPWD");
		errn = update_pwd(state, old_pwd);
		return(! errn);
	}
	return (! update_pwd(state, new_path));
}
