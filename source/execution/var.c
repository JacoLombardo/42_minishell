/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 16:39:03 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/20 14:07:59 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/* Checks if the VAR name is valid */

int	ft_check_var_valid(char *var)
{
	int		status;
	char	*name;

	name = ft_dup_var_name(var);
	if ((name[0] < 65) || (90 < name[0] && name[0] < 95) || (name[0] == 96)
		|| (name[0] > 122))
		status = 1;
	else if (ft_strrchr(name, '-') || ft_strrchr(name, ' ') || ft_strrchr(name,
			'$') || ft_strrchr(name, '.'))
		status = 1;
	else if (ft_strrchr(name, '(') || ft_strrchr(name, ')') || ft_strrchr(name,
			'[') || ft_strrchr(name, ']'))
		status = 1;
	else if (ft_strrchr(name, '!') || ft_strrchr(name, '&') || ft_strrchr(name,
			'*') || ft_strrchr(name, '@'))
		status = 1;
	else if (ft_strrchr(name, '?') || ft_strrchr(name, '+') || ft_strrchr(name,
			'%') || ft_strrchr(name, '^'))
		status = 1;
	else if (ft_strrchr(name, '	'))
		status = 1;
	else
		status = 0;
	free(name);
	return (status);
}

/* Clones the VAR name */

char	*ft_dup_var_name(char *var)
{
	int		i;
	char	*sub;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	sub = ft_substr(var, 0, i);
	if (!sub)
		return (NULL);
	return (sub);
}

/* Clones the VAR value */

char	*ft_dup_var_value(char *var)
{
	int		i;
	char	*value;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=' && var[i + 1] == '\0')
		value = ft_strdup("=");
	else if (var[i] == '=')
		value = ft_strdup(var + i + 1);
	else
		return (NULL);
	if (!value || !ft_strlen(value))
	{
		free(value);
		return (NULL);
	}
	else
		return (value);
}

/* Extracts the VAR value */

char	*ft_get_var_value(char *var)
{
	int		i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=' && var[i + 1] == '\0')
		return (NULL);
	else if (var[i] == '=')
		return (var + i + 1);
	else
		return (NULL);
}

/* Checks if this specific ENV is the VAR looked for,
	and return the index of the value if so */

int	ft_find_var(char *env, char *name)
{
	int		len;
	char	*sub;

	sub = ft_dup_var_name(env);
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
