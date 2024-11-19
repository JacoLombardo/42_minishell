/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:32 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/19 16:15:22 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	ft_var_to_temp(char *var, t_data *data)
{
	int		fd;
	char	*temp;

	temp = ft_charjoin("/tmp/vars_temp", data->shell_id + '0');
	fd = open(temp, O_CREAT | O_WRONLY | O_APPEND, 0777);
	free(temp);
	ft_putstr_fd(var, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

int	ft_you_decide(char *input, t_data *data)
{
	if (ft_strrchr(input, '=') && ft_check_var_valid(input))
	{
		ft_var_to_temp(input, data);
		return (1);
		/* You close here the call */
	}
	else
		return (0);
	/* You handle it as any cmd, which will result in a "command not found" */
}

char	*ft_temp_to_env(char *var, t_data *data)
{
	int		fd;
	char	*line;
	char	*content;
	char	*temp;

	content = NULL;
	temp = ft_charjoin("/tmp/vars_temp", data->shell_id + '0');
	fd = open(temp, O_RDONLY, 0777);
	free(temp);
	if (fd < 0)
		return (content);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_find_var(line, var))
			content = ft_strndup(line, (ft_strlen(line) - 1));
		free(line);
	}
	close(fd);
	return (content);
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
	new_env[i + 1] = NULL;
	ft_free_tab(env);
	return (new_env);
}

char	*test2(char *var)
{
	int		i;
	int		j;
	int		len;
	char	*temp;
	char	*export;

	i = 0;
	j = 0;
	len = ft_strlen(ft_get_var_name(var)) + ft_strlen(ft_get_var_value2(var))
		+ 3;
	export = (char *)malloc((len + 1) * sizeof(char));
	if (!export)
		return (NULL);
	temp = ft_get_var_name(var);
	while (temp[j])
		export[i++] = temp[j++];
	export[i++] = '=';
	export[i++] = '"';
	j = 0;
	temp = ft_get_var_value2(var);
	if (temp)
	{
		while (temp[j])
			export[i++] = temp[j++];
	}
	export[i++] = '"';
	export[i] = '\0';
	return (export);
}

char	*ft_create_export(char *var)
{
	char	*temp;
	char	*name;
	char	*value;

	name = ft_get_var_name(var);
	if (!name)
		return (NULL);
	printf("name: %s\n", name);
	value = ft_get_var_value(var);
	if (!value)
		temp = ft_strjoinjoin(name, "=", "\"");
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
		printf("here\n");
		len = ft_tablen(data->env);
		var = NULL;
		data->env = ft_reallocenv(data->env, len);
		if (!data->env)
			return (1);
		if (ft_strrchr(arg, '='))
			data->env[len] = ft_strdup(arg);
		else
		{
			printf("here1\n");
			data->env[len] = ft_strdup(arg);
			/* var = ft_temp_to_env(arg, data);
			if (var)
				data->env[len] = var;
			else
				data->env[len] = ft_strdup(arg); */
				//data->env[len] = ft_strjoin(arg, "=");
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
