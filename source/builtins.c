/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buildins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 15:54:04 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$')
			printf("%s", ft_getenv(cmd->args[i] + 1, cmd->env));
		else
			printf("%s", cmd->args[i]);
		i++;
	}
	if (!cmd->options)
		printf("\n");
	return (0);
}

void	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	cwd = ft_getenv("PWD", cmd->env);
	printf("%s\n", cwd);
}

void	ft_env(t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->env[i])
	{
		printf("%s\n", cmd->env[i]);
		i++;
	}
}
