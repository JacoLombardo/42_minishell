/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:43 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/12 17:15:50 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_is_numeric(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] == '\0')
		return (0);
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_handle_status(char **args)
{
	if (ft_tablen(args) >= 2 && !ft_is_numeric(args[1]))
	{
		ft_putstr_fd("exit: numeric argument required\n", 2);
		return (2);
	}
	else if (ft_tablen(args) == 2)
		return (ft_atoi(args[1]));
	else if (ft_tablen(args) > 2)
	{
		ft_putstr_fd("exit: too many arguments\n", 2);
		return (1);
	}
	else
		return (0);
}

void	ft_exit(t_full_cmd *cmd, t_data *data)
{
	int	status;

	status = ft_handle_status(cmd->args);
	ft_free_cmd(cmd);
	ft_free_data_temps(data);
	exit(status);
}
