/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:43 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/08 17:58:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_handle_status(char *arg)
{
	int n;

	n = ft_atoi(arg);
	if (!n)
	{
		write(2, "exit: numeric argument required\n", 32);
		return (2);
	}
	else if (n < 0)
		return (156);
	else
		return (n);
}

void	ft_exit(t_full_cmd *cmd, t_data *data)
{
	int	status;

	if (ft_tablen(cmd->args) == 2)
		status = ft_handle_status(cmd->args[1]);
	else if (ft_tablen(cmd->args) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		status = 1;
	}
	else
		status = 0;
	ft_free_cmd(cmd);
	ft_free_data_temps(data);
	exit(status);
}
