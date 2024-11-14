/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 15:11:28 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/14 14:00:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_builtins_error(char *arg, char *error)
{
	if (!ft_strcmp(error, "export"))
	{
		ft_putstr_fd("export: '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (1);
}

int	ft_file_error(char *path, int error)
{
	ft_putstr_fd(path, 2);
	if (error == 1)
	{
		ft_putstr_fd(": command not found\n", 2);
		return (127);
	}
	else if (error == 2)
	{
		ft_putstr_fd(": Is a directory\n", 2);
		return (126);
	}
	else if (error == 3)
	{
		ft_putstr_fd(": Permission denied\n", 2);
		return (126);
	}
	else if (error == 4)
	{
		ft_putstr_fd(": No such file or directory\n", 2);
		return (127);
	}
	return (1);
}

void	ft_error(char *error, int status)
{
	perror(error);
	exit(status);
}
