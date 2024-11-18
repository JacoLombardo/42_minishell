/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:27:59 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/18 11:41:56 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int	status;

	if (*pipex.prev_fd != -1)
	{
		if (dup2(*pipex.prev_fd, STDIN_FILENO) == -1)
			exit(ft_pipe_error(cmd, data, pipex, "dup2 failed for input"));
		close(*pipex.prev_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) == -1)
			exit(ft_pipe_error(cmd, data, pipex, "dup2 failed for output"));
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	status = ft_exec(cmd, data);
	ft_free_reachable(cmd, data);
	exit(status);
}

int	ft_parent(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int	status;

	(void)cmd;
	(void)data;
	status = 0;
	close(pipex.pipe_fd[1]);
	if (*pipex.prev_fd != -1)
		close(*pipex.prev_fd);
	if (cmd->next)
		*pipex.prev_fd = pipex.pipe_fd[0];
	else
	{
		close(pipex.pipe_fd[0]);
		*pipex.prev_fd = -1;
	}
	if (!cmd->next)
		waitpid(pipex.pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int	ft_fork(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int	status;

	status = 0;
	pipex.pid = fork();
	if (pipex.pid == -1)
		return (ft_pipe_error(cmd, data, pipex, "fork"));
	if (!pipex.pid)
		ft_child(cmd, data, pipex);
	else
		status = ft_parent(cmd, data, pipex);
	return (status);
}

int	ft_pipe(t_full_cmd *cmd, t_data *data)
{
	t_pipe	pipex;
	int		prev_fd;

	prev_fd = -1;
	pipex.prev_fd = &prev_fd;
	while (cmd)
	{
		if (pipe(pipex.pipe_fd) == -1)
			return (ft_pipe_error(cmd, data, pipex, "pipe"));
		if (ft_fork(cmd, data, pipex))
			return (ft_pipe_error(cmd, data, pipex, NULL));
		cmd = cmd->next;
	}
	return (0);
}
