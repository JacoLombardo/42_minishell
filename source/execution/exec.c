/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:59:53 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/18 10:21:04 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_select_builtin(t_full_cmd *cmd, t_data *data, int status)
{
	if (!ft_strcmp(cmd->cmd, "echo"))
		status = ft_echo(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		status = ft_cd(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		status = ft_pwd(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		status = ft_export(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		status = ft_unset(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "env"))
		status = ft_env(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		ft_exit(cmd, data);
	return (status);
}

int	ft_builtins(t_full_cmd *cmd, t_data *data, int status)
{
	int	saved_stdin;
	int	saved_stdout;

	saved_stdin = 0;
	saved_stdout = 0;
	if (cmd->redirections)
	{
		if (ft_strcmp(cmd->cmd, "exit"))
		{
			saved_stdin = dup(STDIN_FILENO);
			saved_stdout = dup(STDOUT_FILENO);
		}
		status = ft_redirect(cmd->redirections, cmd->targets, data);
	}
	if (status)
	{
		ft_reset_redirect(saved_stdin, saved_stdout);
		return (status);
	}
	status = ft_select_builtin(cmd, data, status);
	if (cmd->redirections)
		ft_reset_redirect(saved_stdin, saved_stdout);
	return (status);
}

int	ft_exec(t_full_cmd *cmd, t_data *data)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->cmd, "minishell") || !ft_strcmp(cmd->cmd,
			"./minishell"))
		status = ft_subshell(cmd, data, status);
	else if (cmd->built_in == TRUE)
		status = ft_builtins(cmd, data, status);
	else
		status = ft_bin(cmd, data, status);
	return (status);
}

int	ft_if_pipes(t_full_cmd *cmd, t_data *data)
{
	int	status;

	status = 0;
	if (!cmd->operator)
		status = ft_exec(cmd, data);
	else
		status = ft_pipe(cmd, data);
	data->last_exit = status;
	return (status);
}
