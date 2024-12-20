/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:30:41 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/20 09:22:58 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_env(t_full_cmd *cmd, t_data *data)
{
	int		i;

	i = 0;
	if (ft_tablen(cmd->args) > 1)
		return (ft_builtins_error("env", cmd->args[1], 0));
	while (data->env[i])
	{
		if (ft_strchr(data->env[i], '='))
			printf("%s\n", data->env[i]);
		i++;
	}
	return (0);
}
