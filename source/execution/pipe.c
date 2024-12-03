/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 12:27:59 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/03 16:05:37 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

t_full_cmd	*ft_select_cmd(t_full_cmd *cmd, int index)
{
	while (cmd)
	{
		if (cmd->index == index)
			break ;
		cmd = cmd->next;
	}
	return (cmd);
}

void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex)
{
	int			status;

	if (*pipex.prev_fd != -1)
	{
		if (dup2(*pipex.prev_fd, STDIN_FILENO) == -1)
			exit(ft_pipe_error(cmd, data, pipex, "dup2 failed for input"));
		close(*pipex.prev_fd);
	}
	if (pipex.index < (pipex.len - 1))
	{
		if (dup2(pipex.pipe_fd[1], STDOUT_FILENO) == -1)
			exit(ft_pipe_error(cmd, data, pipex, "dup2 failed for output"));
	}
	close(pipex.pipe_fd[0]);
	close(pipex.pipe_fd[1]);
	status = ft_exec(ft_select_cmd(cmd, pipex.index), data);
	exit(ft_clean_house(cmd, data, status, 0));
}

int	ft_parent(t_pipe pipex)
{
	int	status;

	status = 0;
	close(pipex.pipe_fd[1]);
	if (*pipex.prev_fd != -1)
		close(*pipex.prev_fd);
	if (pipex.index < (pipex.len - 1))
		*pipex.prev_fd = pipex.pipe_fd[0];
	else
	{
		close(pipex.pipe_fd[0]);
		*pipex.prev_fd = -1;
	}
	if (pipex.index == (pipex.len - 1))
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
		status = ft_parent(pipex);
	return (status);
}

int	ft_pipe(t_full_cmd *cmd, t_data *data)
{
	int		i;
	int		len;
	int 	status;
	t_pipe	pipex;
	int		prev_fd;

	i = 0;
	len = ft_listlen(cmd);
	status = 0;
	prev_fd = -1;
	pipex.prev_fd = &prev_fd;
	pipex.len = len;
	while (i < len)
	{
		if (pipe(pipex.pipe_fd) == -1)
			return (ft_pipe_error(cmd, data, pipex, "pipe"));
		pipex.index = i;
		status = ft_fork(cmd, data, pipex);
		if (status == -1)
			return (ft_pipe_error(cmd, data, pipex, NULL));
		i++;
	}
	while (waitpid(-1, NULL, 0) > 0) { }
	return (status);
}
