/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:32 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/19 13:55:00 by jalombar         ###   ########.fr       */
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
	new_env[i + 1] = NULL;
	ft_free_tab(env);
	return (new_env);
}

char	*ft_create_export(char *var)
{
	char	*temp;
	char	*name;
	char	*value;

	name = ft_get_var_name(var);
	if (!name)
		return (NULL);
	value = ft_get_var_value(var);
	if (!value)
		return (NULL);
	free(var);
	temp = ft_strjoinjoin(name, "=", "\"");
	if (!temp)
		return (NULL);
	if (value)
		var = ft_strjoinjoin(temp, value, "\"");
	else
		var = ft_charjoin(temp, '"');
	if (!var)
		return (NULL);
	free(temp);
	free(name);
	free(value);
	return (var);
}

int	ft_print_export(char **env)
{
	int		i;
	char	**exports;

	i = 0;
	exports = ft_tab_sort(ft_cpyenv(env));
	if (!exports)
		return (1);
	while (exports[i])
	{
		exports[i] = ft_create_export(exports[i]);
		if (!exports[i])
			return (1);
		printf("declare -x %s\n", exports[i]);
		i++;
	}
	ft_free_tab(exports);
	return (0);
}

int	ft_handle_export(char *arg, t_data *data)
{
	int		len;
	char	*var;

	if (!ft_change_env(arg, data))
	{
		len = ft_tablen(data->env);
		var = NULL;
		data->env = ft_reallocenv(data->env, len);
		if (!data->env)
			return (1);
		if (ft_strrchr(arg, '='))
			data->env[len] = ft_strdup(arg);
		else
		{
			var = ft_temp_to_env(arg, data);
			if (var)
				data->env[len] = var;
			else
				data->env[len] = ft_strjoin(arg, "=");
		}
	}
	return (0);
}

int	ft_export(t_full_cmd *cmd, t_data *data)
{
	int	i;
	int	status;

	i = 1;
	status = 0;
	while (cmd->args[i])
	{
		if (ft_check_var_valid(cmd->args[i]))
			status = ft_builtins_error("export", cmd->args[i],0);
		else
		{
			if (ft_handle_export(cmd->args[i], data))
				return (1);
		}
		i++;
	}
	if (ft_tablen(cmd->args) == 1)
	{
		if (ft_print_export(data->env))
			return (1);
	}
	return (status);
}
