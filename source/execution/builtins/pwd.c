/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:28:54 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:30:31 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

int	ft_pwd(t_full_cmd *cmd, t_data *data)
{
	char	*cwd;

	(void)cmd;
	cwd = ft_getenv("PWD", data->env);
	printf("%s\n", cwd);
	return (0);
}

int	ft_set_pwd(char *pwd, t_data *data, int swap)
{
	char	*temp;

	temp = NULL;
	if (swap)
	{
		if (!ft_getenv("OLDPWD", data->env))
			return (1);
		temp = ft_strdup(ft_getenv("OLDPWD", data->env));
		if (!ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data->env))
			return (1);
		if (!ft_setenv("PWD", temp, data->env))
			return (1);
		free(temp);
	}
	else
	{
		if (ft_getenv("OLDPWD", data->env))
		{
			if (!ft_setenv("OLDPWD", ft_getenv("PWD", data->env), data->env))
				return (1);
		}
		if (!ft_setenv("PWD", pwd, data->env))
			return (1);
	}
	return (0);
}
