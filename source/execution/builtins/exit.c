/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:43 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/18 17:23:53 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_is_long(char *str, char *llong_max, char *llong_min)
{
	int	negative;

	negative = 0;
	if (*str == '\0')
		return (0);
	if (*str == '-')
		negative = 1;
	if (*str == '-' || *str == '+')
		str++;
	if (negative)
	{
		if (ft_strlen(str) > 19)
			return (1);
		if (ft_strlen(str) < 19)
			return (0);
		return (ft_strcmp(str, llong_min + 1) > 0);
	}
	else
	{
		if (ft_strlen(str) > 19)
			return (1);
		if (ft_strlen(str) < 19)
			return (0);
		return (ft_strcmp(str, llong_max) > 0);
	}
}

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
	{
		if (ft_is_long(args[1], "9223372036854775807", "-9223372036854775808"))
		{
			ft_putstr_fd("exit: numeric argument required\n", 2);
			return (2);
		}
		else
			return (ft_atoi(args[1]));
	}
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
	//ft_free_cmd(cmd);
	cleanup_jacopo(cmd);
	ft_free_data_temps(data, 0);
	exit(status);
}
