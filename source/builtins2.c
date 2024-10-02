/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:30:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/02 11:32:41 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd, t_data *data)
{
	char	*cwd;
	char	*path;

	cwd = ft_getenv("PWD", data->env);
	if (cmd->args[0][0] != '~')
		path = ft_strjoinjoin(cwd, "/", cmd->args[0]);
	else
		path = ft_strdup(cmd->args[0] + 1);
	if (chdir(path))
	{
		perror("cd");
		free(path);
		return (0);
	}
	else
	{
		ft_setenv("PWD", path, data->env);
		free(path);
		return (1);
	}
}

int	ft_export(t_cmd *cmd, t_data *data)
{
	int	len;

	len = 0;
	while (data->env[len])
		len++;
	data->env = ft_reallocenv(data->env, len);
	if (!data->env)
		return (0);
	data->env[len] = ft_strjoinjoin(cmd->args[0], "=", cmd->args[1]);
	data->env[len + 1] = NULL;
	return (1);
}

int	ft_unset(t_cmd *cmd, t_data *data)
{
	int	len;

	len = 0;
	while (data->env[len])
		len++;
	data->env = ft_deallocenv(data->env, len, cmd->args[0]);
	if (!data->env)
		return (0);
	else
		return (1);
}
