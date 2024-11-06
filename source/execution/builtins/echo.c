/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:13 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/06 16:59:08 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_echo(t_full_cmd *cmd, t_data *data)
{
	int		i;

	(void)data;
	if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-n"))
		i = 2;
	else
		i = 1;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-n"))
		printf("");
	else
		printf("\n");
	return (0);
}

