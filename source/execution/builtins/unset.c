/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:30 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:32:37 by jalombar         ###   ########.fr       */
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
	new_env[i] = NULL;
	ft_free_tab(env);
	return (new_env);
}

int	ft_unset(t_full_cmd *cmd, t_data *data)
{
	int	len;

	len = ft_tablen(data->env);
	data->env = ft_deallocenv(data->env, len, cmd->args[0]);
	if (!data->env)
		return (1);
	else
		return (0);
}
