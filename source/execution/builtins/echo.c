/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:13 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/07 10:01:34 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_echo(t_full_cmd *cmd, t_data *data)
{
	int		i;
	int	n_flag;

	(void)data;
	n_flag = 0;
	if (cmd->args[1] && !ft_strcmp(cmd->args[1], "-n"))
	{
		n_flag = 1;
		i = 2;
	}
	else
		i = 1;
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		i++;
		if (cmd->args[i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
