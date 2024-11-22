/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:13 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/15 11:05:10 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_check_n_flags(char *arg)
{
	int	i;

	i = 2;
	if (!ft_strncmp(arg, "-n", 2))
	{
		while (arg[i])
		{
			if (arg[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

int	ft_echo(t_full_cmd *cmd, t_data *data)
{
	int	i;
	int	n_flag;

	(void)data;
	n_flag = 0;
	i = 1;
	while (cmd->args[i] && ft_check_n_flags(cmd->args[i]))
	{
		n_flag = 1;
		i++;
	}
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
