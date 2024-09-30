/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 15:30:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 15:41:27 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_cd(t_cmd *cmd)
{
	char	*cwd;
	char	*path;

	cwd = ft_getenv("PWD", cmd->env);
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
		ft_setenv("PWD", path, cmd->env);
		free(path);
		return (1);
	}
}

int	ft_export(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->env[len])
		len++;
	cmd->env = ft_reallocenv(cmd->env, len);
	if (!cmd->env)
		return (0);
	cmd->env[len] = ft_strjoinjoin(cmd->args[0], "=", cmd->args[1]);
	cmd->env[len + 1] = NULL;
	return (1);
}

int	ft_unset(t_cmd *cmd)
{
	int	len;

	len = 0;
	while (cmd->env[len])
		len++;
	cmd->env = ft_deallocenv(cmd->env, len, cmd->args[0]);
	if (!cmd->env)
		return (0);
	else
		return (1);
}
