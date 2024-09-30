/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 11:52:38 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_cpyenv(char **env)
{
	char	**env_cpy;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_cpy = (char **)malloc(i + 1 * sizeof(char *));
	i = 0;
	while (env[i])
	{
		env_cpy[i] = ft_strdup(env[i]);
		i++;
	}
	env_cpy[i] = NULL;
	return (env_cpy);
}

char	*ft_getenv(char *name, char **env)
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
			return (env[i] + j + 1);
		}
		free(sub);
		i++;
	}
	return (NULL);
}

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
