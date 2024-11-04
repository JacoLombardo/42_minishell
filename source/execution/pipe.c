/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:27:59 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/22 12:08:20 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag)
{
	int	status;

	if (*pipex.prev_fd != -1)
	{
		dup2(*pipex.prev_fd, STDIN_FILENO);
		close(*pipex.prev_fd);
	}
	if (flag)
	{
		dup2(pipex.pipe_fd[1], STDOUT_FILENO);
		close(pipex.pipe_fd[1]);
	}
	close(pipex.pipe_fd[0]);
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
	*pipex.prev_fd = pipex.pipe_fd[0];
	waitpid(pipex.pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
		return (1);
}

int	ft_fork(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag)
{
	int	status;

	status = 0;
	pipex.pid = fork();
	if (pipex.pid == -1)
		ft_error("fork", EXIT_FAILURE);
	if (!pipex.pid)
		ft_child(cmd, data, pipex, flag);
	else
		status = ft_parent(cmd, data, pipex);
	return (status);
}

int	ft_pipe2(t_full_cmd **cmd, t_data *data, int count)
{
	int		i;
	t_pipe	pipex;
	int		status;
	int		prev_fd;

	prev_fd = -1;
	pipex.prev_fd = &prev_fd;
	i = 0;
	while (i < count)
	{
		if (i < count - 1)
		{
			if (pipe(pipex.pipe_fd) == -1)
				ft_error("pipe", EXIT_FAILURE);
			status = ft_fork(*cmd, data, pipex, 1);
			*cmd = (*cmd)->next;
		}
		else
			status = ft_fork(*cmd, data, pipex, 0);
		i++;
	}
	return (WEXITSTATUS(status));
}

int	ft_pipe(t_full_cmd **cmd, t_data *data, int count)
{
	int		i;
	t_pipe	pipex;
	int		status;
	int		prev_fd;

	prev_fd = -1;
	pipex.prev_fd = &prev_fd;
	i = 0;
	while (i < count)
	{
		if (i < count - 1)
		{
			if (pipe(pipex.pipe_fd) == -1)
				ft_error("pipe", EXIT_FAILURE);
			status = ft_fork(*cmd, data, pipex, 1);
		}
		else
			status = ft_fork(*cmd, data, pipex, 0);
		i++;
		*cmd = (*cmd)->next;
	}
	return (WEXITSTATUS(status));
}
