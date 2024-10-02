/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:59:47 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/02 12:07:47 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	fd;

	fd = ft_open_file(cmd->args[1], 0);
	dup2(fd, 0);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	ft_exec(cmd->args[2], data);
}

void	ft_parent(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	fd;

	fd = ft_open_file(cmd->args[4], 1);
	dup2(fd, 1);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	ft_exec(cmd->args[3], data);
}

void	ft_pipex(t_cmd *cmd, t_data *data)
{
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_child(cmd, data, p_fd);
	ft_parent(cmd, data, p_fd);
}
