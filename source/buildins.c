/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 12:22:27 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmd *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd);
		i++;
	}
	if (!cmd->options)
		ft_putchar_fd('\n', fd);
	return (0);
}

int	ft_pwd(t_cmd *cmd, int fd)
{
	char	*cwd;

	(void)cmd;
	cwd = ft_getenv("PWD", cmd->env);
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	return (0);
}

int	ft_env(t_cmd *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		ft_putstr_fd(cmd->env[i], fd);
		ft_putchar_fd('\n', fd);
		ft_putchar_fd('\n', fd);
		i++;
	}
	ft_putchar_fd('\n', fd);
	return (0);
}

int	ft_cd(t_cmd *cmd, int fd)
{
	char	*cwd;
	char	*path;

	(void)fd;
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
		//ft_env(cmd, fd);
		free(path);
		return (1);
	}
}
