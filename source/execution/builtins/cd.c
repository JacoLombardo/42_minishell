/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/08 15:34:48 by jalombar         ###   ########.fr       */
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
		if (!ft_strcmp(arg + i, ".."))
			return (ft_back(path, NULL));
		else if (!ft_strncmp(arg + i, "../", 3))
			path = ft_back(path, &i);
		else
			path = ft_forward(path, arg, &i);
	}
	return (path);
}

int	ft_cd(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;
	char	*path;

	cwd = ft_getenv("PWD", data->env);
	if (!ft_strcmp(cmd->args[1], "."))
		return (0);
	path = ft_move(cwd, cmd->args[1]);
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
