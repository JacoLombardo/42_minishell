/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:32:12 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/* Copies the original env to be able to manipulate it */

char	**ft_cpyenv(char **env)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = (char **)malloc((ft_tablen(env) + 2) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i + j] = ft_strdup(env[i]);
		if (!new_env)
			return (NULL);
		if (!ft_strncmp(env[i], "PWD", 3))
		{
			j++;
			new_env[i + j] = ft_strjoin("OLD_", env[i]);
		}
		i++;
	}
	new_env[i + j] = NULL;
	return (new_env);
}

/* Finds a VAR in the env and returns its content */

char	*ft_getenv(char *name, char **env)
{
	int		i;
	int		var;

	i = 0;
	while (env[i])
	{
		var = ft_find_var(env[i], name);
		if (var)
			return (env[i] + var);
		i++;
	}
	return (NULL);
}

/* Adds a new VAR to the env */

char	*ft_setenv(char *name, char *value, char **env)
{
	int		i;
	int		j;
	char	*sub;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[i][j] && env[i][j] != '=')
			j++;
		sub = ft_substr(env[i], 0, j);
		if (ft_strcmp(sub, name) == 0)
		{
			free(sub);
			free(env[i]);
			env[i] = ft_strjoinjoin(name, "=", value);
			return (env[i]);
		}
		free(sub);
		i++;
	}
	return (NULL);
}
