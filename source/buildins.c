/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/25 16:24:58 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmd *cmd, int fd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		ft_putstr_fd(cmd->args[i], fd);
		i++;
	}
	if (!cmd->options)
		ft_putchar_fd('\n', fd);
	return (0);
}

int	ft_pwd(t_cmd *cmd, int fd)
{
	char	*cwd;

	(void)cmd;
	cwd = getcwd(NULL, 0);
	ft_putstr_fd(cwd, fd);
	ft_putchar_fd('\n', fd);
	free(cwd);
	return (0);
}

