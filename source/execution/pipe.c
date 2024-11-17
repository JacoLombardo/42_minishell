/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:27:59 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/17 15:46:27 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_close_fds(t_pipe pipex)
{
	if (*pipex.prev_fd != -1)
		close(*pipex.prev_fd);
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	return (1);
}

void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int	status;

	if (*pipex.prev_fd != -1)
	{
		if (dup2(*pipex.prev_fd, STDIN_FILENO) == -1)
		{
			perror("dup2 failed for input");
			exit(ft_close_fds(pipex));
		}
		close(*pipex.prev_fd);
	}
	if (cmd->next)
	{
		if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) == -1)
		{
			perror("dup2 failed for output");
			exit(ft_close_fds(pipex));
		}
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	status = ft_exec(cmd, data);
	exit(status);
}

int	ft_parent(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int	status;

	(void)cmd;
	(void)data;
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
	{
		perror("fork");
		return (ft_close_fds(pipex));
	}
	if (!pipex.pid)
		ft_child(cmd, data, pipex);
	else
		status = ft_parent(cmd, data, pipex);
	return (status);
}

int	ft_pipe(t_full_cmd *cmd, t_data *data)
{
	int status;
	t_pipe	pipex;
	int		prev_fd;

	prev_fd = -1;
	pipex.prev_fd = &prev_fd;
	while (cmd)
	{
		if (pipe(pipex.pipe_fd) == -1)
		{
			perror("pipe");
			return (ft_close_fds(pipex));
		}
		status = ft_fork(cmd, data, pipex);
		if (status)
		{
			ft_close_fds(pipex);
			return (status);
		}
		cmd = cmd->next;
	}
	// while (waitpid(-1, NULL, 0) > 0) { }
	// if (*pipex.prev_fd != -1)
	// 	close(*pipex.prev_fd);
	return (0);
}
