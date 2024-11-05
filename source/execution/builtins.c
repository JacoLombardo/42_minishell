/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:37:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:35:10 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

// int	ft_echo(t_full_cmd *cmd, t_data *data)
// {
// 	int		i;
// 	char	*line;
// 	char	*temp;

// 	(void)data;
// 	if (!ft_strcmp(cmd->args[1], "-n"))
// 		i = 2;
// 	else
// 		i = 1;
// 	line = ft_strdup(cmd->args[i++]);
// 	while (cmd->args[i])
// 	{
// 		temp = line;
// 		line = ft_strjoin(temp, cmd->args[i]);
// 		if (!line)
// 			return (1);
// 		free(temp);
// 		i++;
// 	}
// 	if (!ft_strcmp(cmd->args[1], "-n"))
// 		printf("%s", line);
// 	else
// 		printf("%s\n", line);
// 	free(line);
// 	return (0);
// }

// int	ft_pwd(t_full_cmd *cmd, t_data *data)
// {
// 	char	*cwd;

// 	(void)cmd;
// 	cwd = ft_getenv("PWD", data->env);
// 	printf("%s\n", cwd);
// 	return (0);
// }

// int	ft_env(t_full_cmd *cmd, t_data *data)
// {
// 	int	i;

// 	(void)cmd;
// 	i = 0;
// 	while (data->env[i])
// 	{
// 		printf("%s\n", data->env[i]);
// 		i++;
// 	}
// 	return (0);
// }
