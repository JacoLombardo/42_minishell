/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:59:53 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/07 15:41:27 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

void	ft_external(t_cmd *cmd, t_data *data)
{
	char	*path;
	pid_t	pid;
	int		status;

	path = ft_get_path(cmd->cmd, data->env);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		if (execve(path, cmd->args, data->env) == -1)
		{
			perror(cmd->cmd);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->last_exit = WEXITSTATUS(status);
	}
}

void	ft_exec(t_cmd *cmd, t_data *data)
{
	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	if (!ft_strcmp(cmd->cmd, "echo"))
		data->last_exit = ft_echo(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "cd"))
		data->last_exit = ft_cd(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "pwd"))
		data->last_exit = ft_pwd(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "export"))
		data->last_exit = ft_export(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "unset"))
		data->last_exit = ft_unset(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "env"))
		data->last_exit = ft_env(cmd, data);
	else if (!ft_strcmp(cmd->cmd, "exit"))
		data->last_exit = ft_exit(cmd, data);
	else
		ft_external(cmd, data);
	if (cmd->redirection)
		ft_reset_redirect(cmd->target, cmd->redirection);
}

/* int	ft_check_operators(t_ast *ast, t_data *data)
{
	if ()
} */

/* void	ft_exec(t_cmd *cmd, t_data *data)
{
	char	**s_cmd;
	char	*path;
	pid_t	pid;
	int		status;

	s_cmd = ft_split(cmd, ' ');
	path = ft_get_path(s_cmd[0], data->env);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		if (execve(path, s_cmd, data->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(s_cmd[0], 2);
			ft_free_tab(s_cmd);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ft_new_ex_stat(&data->ex_stat, WEXITSTATUS(status), cmd);
	}
	ft_free_tab(s_cmd);
} */
