/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:09:40 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/13 17:23:05 by jalombar         ###   ########.fr       */
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

int	ft_is_function(char *path)
{
	struct stat	statbuf;

	stat(path, &statbuf);
	if (S_ISDIR(statbuf.st_mode))
	{
		if ((path[0] == '.' && path[1] == '/') || path[0] == '/')
			return (ft_file_error(path, 2));
		else
			return (ft_file_error(path, 1));
	}
	else if (S_ISREG(statbuf.st_mode))
	{
		if (statbuf.st_mode & S_IXUSR)
			return (0);
		else
			return (ft_file_error(path, 3));
	}
	else
	{
		if (path[0] == '/' || (path[0] == '.' && path[1] == '/'))
			return (ft_file_error(path, 4));
		else
			return (ft_file_error(path, 1));
	}
}

void	ft_bin_child(t_full_cmd *cmd, t_data *data, int status, char *path)
{
	if (cmd->redirections)
		status = ft_redirect(cmd->redirections, cmd->targets, data);
	if (status == 1)
		exit(status);
	if (execve(path, cmd->args, data->env) == -1)
		ft_error(cmd->cmd, 1);
}

int	ft_bin(t_full_cmd *cmd, t_data *data, int status)
{
	char	*path;
	pid_t	pid;
	int		error;

	path = ft_get_path(cmd->cmd, data->env);
	error = ft_is_function(path);
	if (error)
		return (error);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_bin_child(cmd, data, status, path);
	else
	{
		waitpid(pid, &status, 0);
		free(path);
		if (WIFEXITED(status))
			return (WEXITSTATUS(status));
	}
	return (status);
}
