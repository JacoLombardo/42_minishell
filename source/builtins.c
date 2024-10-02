/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/02 11:34:03 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_echo(t_cmd *cmd, t_data *data)
{
	int	i;

	i = 0;
	while (cmd->args[i])
	{
		if (cmd->args[i][0] == '$')
			printf("%s", ft_getenv(cmd->args[i] + 1, data->env));
		else
			printf("%s", cmd->args[i]);
		i++;
	}
	if (!cmd->options)
		printf("\n");
	return (0);
}

void	ft_pwd(t_cmd *cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	cwd = ft_getenv("PWD", data->env);
	printf("%s\n", cwd);
}

void	ft_env(t_cmd *cmd, t_data *data)
{
	int	i;

	(void)cmd;
	i = 0;
	while (data->env[i])
	{
		printf("%s\n", data->env[i]);
		i++;
	}
}
