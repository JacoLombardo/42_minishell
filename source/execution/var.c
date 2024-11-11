/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:39:03 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/08 16:39:15 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/* Checks if the VAR name is valid */

int	ft_check_var_valid(char *var)
{
	int	status;
	char *name;

	name = ft_get_var_name(var);
	if ((name[0] < 65) || (90 < name[0] && name[0] < 95) || (name[0] == 96) || (name[0] > 122))
		status = 1;
	else if (ft_strrchr(name, '-') || ft_strrchr(name, ' ') || ft_strrchr(name, '$') || ft_strrchr(name, '.'))
		status = 1;
	else if (ft_strrchr(name, '(') || ft_strrchr(name, ')') || ft_strrchr(name, '[') || ft_strrchr(name, ']'))
		status = 1;
	else if (ft_strrchr(name, '!') || ft_strrchr(name, '&') || ft_strrchr(name, '*') || ft_strrchr(name, '@'))
		status = 1;
	else if (ft_strrchr(name, '?') || ft_strrchr(name, '+') || ft_strrchr(name, '%') || ft_strrchr(name, '^'))
		status = 1;
	else if (ft_strrchr(name, '	'))
		status = 1;
	else
		status = 0;
	free(name);
	return (status);
}

/* Extracts the VAR name */

char	*ft_get_var_name(char *var)
{
	int	i;
	char *sub;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	sub = ft_substr(var, 0, i);
	return (sub);
}

/* Checks if this specific ENV is the VAR looked for, and return its value if so */

int	ft_find_var(char *env, char *name)
{
	int	len;
	char	*sub;

	sub = ft_get_var_name(env);
	len = ft_strlen(sub);
	if (!ft_strcmp(sub, name))
	{
		free(sub);
		return (len + 1);
	}
	else
	{
		free(sub);
		return (0);
	}
}