/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:56:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/15 12:05:10 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_heredoc(char *delimiter)
{
	int		fd;
	char	*line;

	fd = open("/tmp/heredoc_temp", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (fd < 0)
	{
		perror("open");
		exit(1);
	}
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strcmp(line, delimiter))
		{
			free(line);
			break ;
		}
		ft_putstr_fd(line, fd);
		ft_putchar_fd('\n', fd);
		free(line);
	}
}

void	ft_in_redirect(t_redir_type redirection, char *target, int *from_fd, int *to_fd)
{
	if (redirection == R_IN)
	{
		*to_fd = open(target, O_RDONLY, 0777);
		*from_fd = 0;
	}
	else if (redirection == R_HEREDOC)
	{
		*to_fd = open("/tmp/heredoc_temp", O_RDONLY, 0777);
		*from_fd = 0;
	}
}

void	ft_out_redirect(t_redir_type redirection, char *target,  int *from_fd, int *to_fd)
{
	if (redirection == R_OUT)
	{
		*to_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		*from_fd = 1;
	}
	else if (redirection == R_APPEND)
	{
		*to_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0777);
		*from_fd = 1;
	}
}

void	ft_redirect(t_redir_type *redirections, char **targets)
{
	int	i;
	int	from_fd;
	int	to_fd;

	i = 0;
	from_fd = 0;
	to_fd = -1;
	while (redirections[i])
	{
		if (redirections[i] == R_IN || redirections[i] == R_HEREDOC)
			ft_in_redirect(redirections[i], targets[i], &from_fd, &to_fd);
		else if (redirections[i] == R_OUT || redirections[i] == R_APPEND)
			ft_out_redirect(redirections[i], targets[i], &from_fd, &to_fd);
		if (to_fd == -1)
		{
			perror(targets[i]);
			exit(1);
		}
		dup2(to_fd, from_fd);
		i++;
	}
}

void	ft_reset_redirect(t_redir_type *redirections, char **targets)
{
	int	i;
	int	from_fd;
	int	to_fd;

	i = 0;
	from_fd = 0;
	to_fd = -1;
	while (redirections[i])
	{
		if (redirections[i] == R_IN || redirections[i] == R_HEREDOC)
			ft_in_redirect(redirections[i], targets[i], &to_fd, &from_fd);
		else if (redirections[i] == R_OUT || redirections[i] == R_APPEND)
			ft_out_redirect(redirections[i], targets[i], &to_fd, &from_fd);
		if (to_fd == -1)
		{
			perror(targets[i]);
			exit(1);
		}
		dup2(to_fd, from_fd);
		i++;
	}
}
