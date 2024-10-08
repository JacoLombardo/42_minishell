/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 09:59:47 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/08 16:07:03 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	/* if (ret == -1)
		exit(0); */
	return (ret);
}

// void	ft_childx(t_cmd *cmd, t_data *data, int *p_fd)
// {
// 	int	fd;

// 	fd = ft_open_file(cmd->args[1], 0);
// 	dup2(fd, 0);
// 	dup2(p_fd[1], 1);
// 	close(p_fd[0]);
// 	ft_exec(cmd->args[2], data);
// }

// void	ft_parentx(t_cmd *cmd, t_data *data, int *p_fd)
// {
// 	int	fd;

// 	fd = ft_open_file(cmd->args[4], 1);
// 	dup2(fd, 1);
// 	dup2(p_fd[0], 0);
// 	close(p_fd[1]);
// 	ft_exec(cmd->args[3], data);
// }

// void	ft_pipex(t_cmd *cmd, t_data *data)
// {
// 	int		p_fd[2];
// 	pid_t	pid;

// 	if (pipe(p_fd) == -1)
// 		exit(-1);
// 	pid = fork();
// 	if (pid == -1)
// 		exit(-1);
// 	if (!pid)
// 		ft_childx(cmd, data, p_fd);
// 	ft_parentx(cmd, data, p_fd);
// }
