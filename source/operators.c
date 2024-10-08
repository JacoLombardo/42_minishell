/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/08 10:03:36 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_logical_and(t_cmd *cmd, t_data *data, int exit)
{
	if (!exit)
		exit = ft_exec(cmd, data);
	return (exit);
}

int	ft_logical_or(t_cmd *cmd, t_data *data, int exit)
{
	if (exit > 0 || exit < 0)
		exit = ft_exec(cmd, data);
	return (exit);
}

int	ft_child(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	exit;

	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	exit = ft_exec(cmd, data);
	return (exit);
}

int	ft_parent(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	exit;

	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	exit = ft_exec(cmd, data);
	return (exit);
}

int	ft_fork(t_cmd *cmd, t_data *data)
{
	int	exit;
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_child(cmd, data, p_fd);
	exit = ft_parent(cmd->next, data, p_fd);
	return (exit);
}

int	ft_pipe(t_cmd *cmd, t_data *data, int count)
{
	int	i;
	int	exit;

	i = 0;
	while (i < count);
	{

	}
}

// int	ft_pipe(t_cmd *cmd, t_data *data)
// {
// 	int	exit;
// 	int		p_fd[2];
// 	pid_t	pid;

// 	if (pipe(p_fd) == -1)
// 		exit(-1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (!pid)
// 		ft_child(cmd, data, p_fd);
// 	exit = ft_parent(cmd->next, data, p_fd);
// 	return (exit);
// }
