/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:59:53 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/31 16:55:08 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = 0;
	allpath = ft_split(ft_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_both_tab(allpath, s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_both_tab(allpath, s_cmd);
	return (cmd);
}

int	ft_external(t_full_cmd *cmd, t_data *data)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = ft_get_path(cmd->cmd, data->env);
	pid = fork();
	status = 0;
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		if (cmd->redirections)
			ft_redirect(cmd->redirections, cmd->targets);
		if (execve(path, cmd->args, data->env) == -1)
			ft_error(cmd->cmd, 1);
	}
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}

int	ft_builtins(t_full_cmd *cmd, t_data *data)
{
	int	status;
	int	saved_stdin;
	int	saved_stdout;

	status = 0;
	saved_stdin = dup(STDIN_FILENO);
	saved_stdout = dup(STDOUT_FILENO);
	if (cmd->redirections)
		ft_redirect(cmd->redirections, cmd->targets);
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
	if (cmd->redirections)
		ft_reset_redirect(cmd->redirections, saved_stdin, saved_stdout);
	return (status);
}

int	ft_exec(t_full_cmd *cmd, t_data *data)
{
	if (cmd->built_in == TRUE)
		data->last_exit = ft_builtins(cmd, data);
	else
		data->last_exit = ft_external(cmd, data);
	return (data->last_exit);
}

int	ft_check_operators3(t_full_cmd *cmd, t_data *data)
{
	int	status;

	if (!cmd->operator)
		status = ft_exec(cmd, data);
	else
		status = ft_handle_pipe2(&cmd, data);
	return (status);
}

int	ft_check_operators2(t_full_cmd *cmd, t_data *data)
{
	int	status;

	if (!cmd->operator)
		status = ft_exec(cmd, data);
	else
	{
		status = ft_handle_pipe2(&cmd, data);
		while (cmd)
		{
			if (!ft_strcmp(cmd->operator, "&&"))
				status = ft_logical_and2(&cmd, data, status);
			else if (!ft_strcmp(cmd->operator, "||"))
				status = ft_logical_or2(&cmd, data, status);
		}
	}
	return (status);
}

int	ft_check_operators(t_ast *ast, t_data *data)
{
	int			status;
	t_full_cmd	*cmd;
	char		**operators;

	cmd = *ast->cmds;
	operators = ast->operators;
	if (!operators)
		status = ft_exec(*ast->cmds, data);
	else
	{
		status = ft_handle_pipe(&cmd, data, &operators);
		while (*operators && cmd)
		{
			if (!ft_strcmp(*operators, "&&"))
				status = ft_logical_and(&cmd, data, &operators, status);
			else if (!ft_strcmp(*operators, "||"))
				ft_logical_or(&cmd, data, &operators, status);
		}
	}
	return (status);
}
