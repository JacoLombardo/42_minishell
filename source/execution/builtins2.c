/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:30:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/22 15:17:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*ft_back_to_parent(char *cwd)
{
	int		i;
	int		len;
	char	*path;

	i = 0;
	len = ft_strlen(cwd);
	while (cwd[len - i - 1] != '/')
		i++;
	path = ft_strndup(cwd, (len - 1 - i));
	return (path);
}

char	*ft_move_back(char *cwd, char *arg)
{
	int		i;
	int		len;
	char	*path;
	char	*temp;

	i = 0;
	len = 0;
	path = cwd;
	printf("LEN: %zu\n\n", ft_strlen(arg));
	while (i < (int)ft_strlen(arg))
	{
		printf("START path: %s, i: %i, arg: %s\n\n", path, i, arg + i);
		if (!ft_strncmp(arg + i, "../", 3))
		{
			i += 3;
			path = ft_back_to_parent(path);
		}
		else
		{
			while (arg[i + len] && arg[i + len] != '/')
				len++;
			temp = ft_strndup(arg + i, len);
			path = ft_strjoinjoin(path, "/", temp);
			free(temp);
			printf("temp: %s\n", path);
			i += len + 1;
		}
	}
	return (path);
}

char	*ft_test_back(char *temp, int *i)
{
	int		len;
	char	*path;

	len = ft_strlen(temp);
	while (temp[len - *i - 1] != '/')
		(*i)++;
	path = ft_strndup(temp, (len - 1 - *i));
	free(temp);
	*i += 3;
	return (path);
}

char	*ft_test(char *temp, char *arg, int *i)
{
	int		len;
	char	*path;
	char	*temp2;

	len = 0;
	while (arg[*i + len] && arg[*i + len] != '/')
		len++;
	temp2 = ft_strndup(arg + *i, len);
	path = ft_strjoinjoin(temp, "/", temp2);
	free(temp);
	free(temp2);
	*i += len + 1;
	return (path);
}

char	*ft_move(char *cwd, char *arg)
{
	int		i;
	char	*path;

	i = 0;
	path = ft_strdup(cwd);
	while (i < (int)ft_strlen(arg))
	{
		if (!ft_strcmp(arg, ".."))
			path = ft_test_back(path, &i);
		else if (!ft_strncmp(arg + i, "../", 3))
			path = ft_test_back(path, &i);
		else
			path = ft_test(path, arg, &i);
	}
	return (path);
}

int	ft_cd(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;
	char	*path;

	cwd = ft_getenv("PWD", data->env);
	printf("PWD: %s\n", cwd);
	path = ft_move(cwd, cmd->args[1]);
/* 	if (!ft_strcmp(cmd->args[1], ".."))
		path = ft_back_to_parent(cwd);
	else if (!ft_strncmp(cmd->args[1], "../", 3))
		path = ft_move_back(cwd, cmd->args[1]);
	else if (cmd->args[1][0] != '~')
		path = ft_strjoinjoin(cwd, "/", cmd->args[1]);
	else
		path = ft_strdup(cmd->args[1] + 1); */
	printf("TEST: %s\n", path);
	if (chdir(path))
	{
		perror(path);
		free(path);
		return (1);
	}
	else
	{
		ft_setenv("OLD_PWD", cwd, data->env);
		ft_setenv("PWD", path, data->env);
		free(path);
		return (0);
	}
}

int	ft_export(t_full_cmd *cmd, t_data *data)
{
	int	len;

	len = ft_tablen(data->env);
	data->env = ft_reallocenv(data->env, len);
	if (!data->env)
		return (1);
	data->env[len] = ft_strjoinjoin(cmd->args[0], "=", cmd->args[1]);
	data->env[len + 1] = NULL;
	return (0);
}

int	ft_unset(t_full_cmd *cmd, t_data *data)
{
	int	len;

	len = ft_tablen(data->env);
	data->env = ft_deallocenv(data->env, len, cmd->args[0]);
	if (!data->env)
		return (1);
	else
		return (0);
}

void	ft_exit(int status, t_data *data)
{
	ft_free_data(data);
	g_program = 1;
	exit(status);
}
