/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 14:47:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/02 09:46:16 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

/* Finds a VAR in ENV and returns its value */
char	*ft_getenv(char *name, char **env)
{
	int	i;
	int	var;

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


/* Adds a new VAR to ENV */
char	*ft_setenv(char *name, char *value, char **env)
{
	int		i;
	char	*sub;

	i = 0;
	while (env[i])
	{
		sub = ft_dup_var_name(env[i]);
		if (!ft_strcmp(sub, name))
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

/* Checks if a VAR is already inside ENV, and it changes its value if so */
int	ft_change_env(char *var, t_data *data)
{
	int		i;
	char	*sub;

	i = 0;
	sub = ft_dup_var_name(var);
	while (data->env[i])
	{
		if (ft_find_var(data->env[i], sub))
		{
			free(sub);
			if (ft_strrchr(var, '='))
			{
				free(data->env[i]);
				data->env[i] = ft_strdup(var);
			}
			return (1);
		}
		i++;
	}
	free(sub);
	return (0);
}

/* Copies the original ENV to be able to manipulate it */
char	**ft_cpyenv(char **env)
{
	char	**new_env;
	int		i;

	i = 0;
	new_env = (char **)malloc((ft_tablen(env) + 1) * sizeof(char *));
	if (!new_env)
		return (ft_malloc_error2(NULL, NULL, 0));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
			return (ft_malloc_error2(NULL, new_env, i));
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
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
