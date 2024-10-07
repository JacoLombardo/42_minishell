/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/07 15:07:01 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_child(t_cmd *cmd, t_data *data, int *p_fd)
{
	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[1], 1);
	close(p_fd[0]);
	ft_exec(cmd, data);
}

void	ft_parent(t_cmd *cmd, t_data *data, int *p_fd)
{
	if (cmd->redirection)
		ft_redirect(cmd->target, cmd->redirection);
	dup2(p_fd[0], 0);
	close(p_fd[1]);
	ft_exec(cmd, data);
}

void	ft_pipe(t_ast *ast, t_data *data)
{
	int		p_fd[2];
	pid_t	pid;
	t_cmd	*cmd;

	cmd = *ast->cmds;
	if (pipe(p_fd) == -1)
		exit(-1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_child(cmd, data, p_fd);
	ft_parent(cmd->next, data, p_fd);
}
