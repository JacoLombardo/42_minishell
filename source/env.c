/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/03 11:50:59 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* Reduces the memory allocation of env and remove a specific VAR */

char	**ft_deallocenv(char **env, int size, char *name)
{
	char	**new_env;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_env = (char **)malloc((size - 1 + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		if (!ft_find_var(env[i], name))
		{
			new_env[j] = ft_strdup(env[i]);
			if (!new_env[j])
				return (NULL);
			j++;
		}
		i++;
	}
	new_env[i] = NULL;
	ft_free_tab(env);
	return (new_env);
}

/* Increses the memory allocation of env by one */

char	**ft_reallocenv(char **env, int size)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc((size + 1 + 1) * sizeof(char *));
	if (!new_env)
		return (NULL);
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
			return (NULL);
		i++;
	}
	new_env[i] = NULL;
	ft_free_tab(env);
	return (new_env);
}

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
	new_env[i] = NULL;
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
