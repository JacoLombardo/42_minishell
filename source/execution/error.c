/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:11:28 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/16 15:26:06 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_put_error(char *s1, char *s2, char *s3, int quotes)
{
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	if (s2)
	{
		if (quotes)
			ft_putstr_fd("'", 2);
		ft_putstr_fd(s2, 2);
		if (quotes)
			ft_putstr_fd("'", 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(s3, 2);
}

int	ft_builtins_error(char *builtin, char *arg)
{
	if (!ft_strcmp(builtin, "export"))
		ft_put_error(builtin, arg, "not a valid identifier\n", 1);
	else if (!ft_strcmp(builtin, "cd") && !arg)
		ft_put_error(builtin, arg, "too many arguments\n", 0);
	else if (!ft_strcmp(builtin, "cd") && arg)
		ft_put_error(builtin, arg, "No such file or directory\n", 0);
	else if (!ft_strcmp(builtin, "env"))
	{
		ft_put_error(builtin, arg, "No such file or directory\n", 1);
		return (127);
	}
	return (1);
}

int	ft_file_error(char *path, int error)
{
	int	status;

	if ((error == 1 || error == 4))
		status = 127;
	else
		status = 126;
	ft_putstr_fd(path, 2);
	if (error == 1)
		ft_putstr_fd(": command not found\n", 2);
	else if (error == 2)
		ft_putstr_fd(": Is a directory\n", 2);
	else if (error == 3)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (error == 4)
		ft_putstr_fd(": No such file or directory\n", 2);
	return (status);
}

void	ft_error(char *error, int status)
{
	perror(error);
	exit(status);
}
