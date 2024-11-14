/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:30:41 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/14 12:26:35 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_env(t_full_cmd *cmd, t_data *data)
{
	int		i;
	char	*value;

	(void)cmd;
	i = 0;
	while (data->env[i])
	{
		value = ft_get_var_value(data->env[i]);
		if (value)
		{
			printf("%s\n", data->env[i]);
			free(value);
		}
		i++;
	}
	return (0);
}
