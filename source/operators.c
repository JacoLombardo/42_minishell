/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/08 18:26:55 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_logical(t_cmd *cmd, t_data *data, char *operator, int status)
{
	if (!ft_strcmp(operator, "&&") && !status)
		status = ft_exec(cmd, data);
	else if (!ft_strcmp(operator, "||") && (status > 0 || status < 0))
		status = ft_exec(cmd, data);
	return (status);
}

int	ft_child(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	status;

	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	status = ft_exec(cmd, data);
	return (status);
}

int	ft_parent(t_cmd *cmd, t_data *data, int *p_fd)
{
	int	status;

	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	status = ft_exec(cmd, data);
	return (status);
}

int	ft_fork(t_cmd *cmd, t_data *data)
{
	int	status;
	int		p_fd[2];
	pid_t	pid;

	if (pipe(p_fd) == -1)
		return (-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_child(cmd, data, p_fd);
	status = ft_parent(cmd->next, data, p_fd);
	return (status);
}

int	ft_pipe(t_cmd **cmd, t_data *data, int count)
{
	int	i;

	(void)data;
	i = 0;
	while (i < count)
	{
		*cmd = (*cmd)->next;
		i++;
	}
	return (0);
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
