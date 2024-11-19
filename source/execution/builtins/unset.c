/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/08 15:27:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

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
	new_env[j] = NULL;
	ft_free_tab(env);
	return (new_env);
}

int	ft_handle_unset(char *arg, t_data *data)
{
	int	len;

	if (ft_getenv(arg, data->env))
	{
		len = ft_tablen(data->env);
		data->env = ft_deallocenv(data->env, len, arg);
		if (!data->env)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	ft_unset(t_full_cmd *cmd, t_data *data)
{
	int		i;

	i = 1;
	while (cmd->args[i])
	{
		if (ft_handle_unset(cmd->args[i], data))
			return (1);
		i++;
	}
	return (0);
}
