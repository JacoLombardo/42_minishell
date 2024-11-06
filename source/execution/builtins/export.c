/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 17:29:32 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/06 15:49:24 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/execution.h"

void	ft_var_to_temp(char *var)
{
	int	fd;

	fd = open("/tmp/vars_temp", O_CREAT | O_WRONLY | O_APPEND, 0777);
	ft_putstr_fd(var, fd);
	ft_putchar_fd('\n', fd);
	close(fd);
}

char	*ft_temp_to_env(char *var)
{
	int		fd;
	char	*line;
	char	*content;

	fd = open("/tmp/vars_temp", O_RDONLY, 0777);
	content = NULL;
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

int	ft_export(t_full_cmd *cmd, t_data *data)
{
	int		len;
	char	*var;

	len = ft_tablen(data->env);
	var = NULL;
	data->env = ft_reallocenv(data->env, len);
	if (!data->env)
		return (1);
	if (ft_strrchr(cmd->args[1], '='))
		data->env[len] = ft_strdup(cmd->args[1]);
	else
	{
		var = ft_temp_to_env(cmd->args[1]);
		if (var)
			data->env[len] = var;
		else
			data->env[len] = ft_strjoin(cmd->args[1], "=");
	}
	return (0);
}