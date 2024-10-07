/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:56:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/07 15:28:27 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_redirect(char *file, char *redirection)
{
	int	fd;
	int	to_fd;

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
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(to_fd, fd);
}

/* void	ft_in_redirect(char *file)
{
	int	fd;

	fd = open(file, O_RDONLY, 0777);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 0);
}

void	ft_out_redirect(char *file)
{
	int	fd;

	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		perror(file);
		exit(1);
	}
	dup2(fd, 1);
} */
