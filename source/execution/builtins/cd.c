/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/08 18:32:10 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

char	*ft_back(char *temp, int *index)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	len = ft_strlen(temp);
	while (temp[len - i - 1] != '/')
		i++;
	path = ft_strndup(temp, (len - 1 - i));
	if (!path)
		return (ft_malloc_error1(temp, NULL, 0));
	free(temp);
	if (index)
		*index += 3;
	return (path);
}

char	*ft_forward(char *temp, char *arg, int *i)
{
	int		len;
	char	*path;
	char	*temp2;

	len = 0;
	while (arg[*i + len] && arg[*i + len] != '/')
		len++;
	temp2 = ft_strndup(arg + *i, len);
	if (!temp2)
		return (ft_malloc_error1(temp, NULL, 0));
	path = ft_strjoinjoin(temp, "/", temp2);
	if (!path)
	{
		free(temp2);
		return (ft_malloc_error1(temp, NULL, 0));
	}
	free(temp);
	free(temp2);
	*i += len + 1;
	return (path);
}

char	*ft_move(char *cwd, char *arg)
{
	int		i;
	char	*path;

	if (arg[0] == '/')
		return (ft_strdup(arg));
	else if (arg[0] == '~')
		i = 2;
	else
		i = 0;
	path = ft_strdup(cwd);
	if (!path)
		return (ft_malloc_error1(NULL, NULL, 0));
	while (i < (int)ft_strlen(arg))
	{
		if (!ft_strcmp(arg + i, ".."))
			return (ft_back(path, NULL));
		else if (!ft_strncmp(arg + i, "../", 3))
			path = ft_back(path, &i);
		else
			path = ft_forward(path, arg, &i);
		if (!path)
			return (NULL);
	}
	return (path);
}

int	ft_special_args(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;

	cwd = ft_getenv("PWD", data->env);
	if (!cmd->args[1])
	{
		ft_set_pwd(ft_getenv("HOME", data->env), data, 0);
		return (0);
	}
	else if (ft_tablen(cmd->args) > 2)
		return (ft_builtins_error("cd", NULL, 0));
	else if (ft_strlen(cmd->args[1]) > 1 && cmd->args[1][0] == '-')
		return (ft_builtins_error("cd", cmd->args[1], 2));
	else if (!ft_strcmp(cmd->args[1], ".") || !ft_strcmp(cmd->args[1], cwd))
		return (0);
	else if (!ft_strcmp(cmd->args[1], "-"))
	{
		ft_set_pwd(NULL, data, 1);
		return (0);
	}
	else
		return (-1);
}

int	ft_cd(t_full_cmd *cmd, t_data *data)
{
	int		status;
	char	*cwd;
	char	*path;

	status = ft_special_args(cmd, data);
	if (status >= 0)
		return (status);
	if (cmd->args[1][0] == '~')
		cwd = ft_getenv("HOME", data->env);
	else
		cwd = ft_getenv("PWD", data->env);
	path = ft_move(cwd, cmd->args[1]);
	if (!path)
		return (1);
	if (chdir(path))
	{
		free(path);
		return (ft_builtins_error("cd", cmd->args[1], 1));
	}
	else
	{
		path = trim_trailing_slash(path);
		ft_set_pwd(path, data, 0);
		free(path);
		return (0);
	}
}
