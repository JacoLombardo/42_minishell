/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:32 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/20 16:38:26 by jalombar         ###   ########.fr       */
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
		return (ft_malloc_error2(NULL, NULL, 0));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		if (!new_env)
			return (ft_malloc_error2(NULL, new_env, i));
		i++;
	}
	new_env[i] = NULL;
	new_env[i + 1] = NULL;
	ft_free_tab(env);
	return (new_env);
}

char	*ft_add_quotes(char *var, char	*name, char *value)
{
	char	*export;
	char	*with_quotes;

	with_quotes = NULL;
	if (value && ft_strchr(var, '='))
	{
		with_quotes = ft_strjoinjoin("=\"", value, "\"");
		if (!with_quotes)
			return (ft_malloc_error1(name, NULL, 0));
	}
	else if (!value && ft_strchr(var, '='))
	{
		with_quotes = ft_strjoin("=\"", "\"");
		if (!with_quotes)
			return (ft_malloc_error1(name, NULL, 0));
	}
	else
		return (name);
	export = ft_strjoin(name, with_quotes);
	free(name);
	if (!export)
		return (ft_malloc_error1(with_quotes, NULL, 0));
	free(with_quotes);
	return (export);
}

int	ft_print_export(char **env)
{
	int		i;
	char	**exps;
	char	*with_quotes;

	i = 0;
	exps = ft_tab_sort(ft_cpyenv(env));
	if (!exps)
		return (ft_malloc_error(NULL, NULL, 0));
	while (exps[i])
	{
		with_quotes = ft_add_quotes(exps[i], ft_dup_var_name(exps[i]), ft_get_var_value(exps[i]));
		if (!with_quotes)
		{
			free(exps);
			return (1);
		}
		printf("declare -x %s\n", with_quotes);
		free(with_quotes);
		free(exps[i]);
		i++;
	}
	free(exps);
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
				data->env[len] = ft_strdup(arg);
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
			status = ft_builtins_error("export", cmd->args[i], 0);
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
