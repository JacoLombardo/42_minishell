/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:56:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/11 15:12:53 by jalombar         ###   ########.fr       */
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

void	ft_in_redirect(char *file, char *redirection, int *from_fd, int *to_fd)
{
	if (!ft_strcmp(redirection, "<"))
	{
		*to_fd = open(file, O_RDONLY, 0777);
		*from_fd = 0;
	}
	else if (!ft_strcmp(redirection, "<<"))
	{
		*to_fd = open("/tmp/heredoc_temp", O_RDONLY, 0777);
		*from_fd = 0;
	}
}

void	ft_out_redirect(char *file, char *redirection, int *from_fd, int *to_fd)
{
	if (!ft_strcmp(redirection, ">"))
	{
		ft_putstr_fd("dentro\n", 2);
		*to_fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		ft_putstr_fd("che cazzo fai\n", *to_fd);
		*from_fd = 1;
	}
	else if (!ft_strcmp(redirection, ">>"))
	{
		*to_fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		*from_fd = 1;
	}
}

void	ft_redirect(char *file, char *redirection)
{
	int	from_fd;
	int	to_fd;

	from_fd = 0;
	to_fd = -1;
	if (!ft_strcmp(redirection, "<") || !ft_strcmp(redirection, "<<"))
		ft_in_redirect(file, redirection, &from_fd, &to_fd);
	else if (!ft_strcmp(redirection, ">") || !ft_strcmp(redirection, ">>"))
		ft_out_redirect(file, redirection, &from_fd, &to_fd);
	if (to_fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(to_fd, from_fd);
}

void	ft_reset_redirect(char *file, char *redirection)
{
	int	from_fd;
	int	to_fd;

	from_fd = 0;
	to_fd = -1;
	if (!ft_strcmp(redirection, "<") || !ft_strcmp(redirection, "<<"))
		ft_in_redirect(file, redirection, &to_fd, &from_fd);
	else if (!ft_strcmp(redirection, ">") || !ft_strcmp(redirection, ">>"))
		ft_out_redirect(file, redirection, &to_fd, &from_fd);
	if (to_fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(to_fd, from_fd);
}

/* void	ft_redirect(char *file, char *redirection)
{
	int	fd;
	int	to_fd;

	fd = -1;
	if (!ft_strcmp(redirection, "<"))
	{
		fd = open(file, O_RDONLY, 0777);
		to_fd = 0;
	}
	else if (!ft_strcmp(redirection, ">"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		to_fd = 1;
	}
	else if (!ft_strcmp(redirection, ">>"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		to_fd = 1;
	}
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, to_fd);
}

void	ft_reset_redirect(char *file, char *redirection)
{
	int	fd;
	int	to_fd;

	fd = -1;
	if (!ft_strcmp(redirection, "<"))
	{
		fd = open(file, O_RDONLY, 0777);
		to_fd = 0;
	}
	else if (!ft_strcmp(redirection, ">"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		to_fd = 1;
	}
	else if (!ft_strcmp(redirection, ">>"))
	{
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
		to_fd = 1;
	}
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(to_fd, fd);
} */
