/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:32 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 17:32:28 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

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

int	ft_export(t_full_cmd *cmd, t_data *data)
{
	int	len;

	len = ft_tablen(data->env);
	data->env = ft_reallocenv(data->env, len);
	if (!data->env)
		return (1);
	data->env[len] = ft_strjoinjoin(cmd->args[0], "=", cmd->args[1]);
	data->env[len + 1] = NULL;
	return (0);
}
