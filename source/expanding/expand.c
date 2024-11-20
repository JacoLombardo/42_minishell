/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:31:21 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/12 11:58:50 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static char	*get_var_name(int i, char *line)
{
	int		var_name_len;
	char	*temp;
	char	*var_name;

	var_name_len = 0;
	if (line[i] == '?')
		temp = ft_strdup("?");
	else
	{
		while (is_bash_valid(line[i]))
		{
			var_name_len++;
			i++;
		}
		temp = ft_substr(line, i - var_name_len, var_name_len);
	}
	var_name = ft_strjoin(temp, "=");
	free(temp);
	return (var_name);
}

static char	*expand_single_var(char *new_line, char *var_name, char *env[])
{
	int		j;
	char	*var_value;

	if (!ft_strncmp(var_name, "=", 1))
	{
		new_line = append_char(new_line, '$');
		return (new_line);
	}
	j = 0;
	while (env[j])
	{
		var_value = ft_better_strnstr(env[j], var_name, ft_strlen(env[j]));
		if (var_value)
		{
			new_line = append_value(new_line, var_value, var_name);
			break ;
		}
		j++;
	}
	return (new_line);
}

static char	*expand_last_exit(char *new_line, int last_exit)
{
	char	*temp;
	char	*exit_str;

	temp = ft_strdup(new_line);
	free(new_line);
	exit_str = ft_itoa(last_exit);
	new_line = ft_strjoin(temp, exit_str);
	free(temp);
	free(exit_str);
	return (new_line);
}

char	*expand_vars(char *line, t_data *data)
{
	int		i;
	char	*var_name;
	char	*new_line;
	char	**temp_env; //

	temp_env = copy_and_enhance_env(data);
	i = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && what_quotes(line + i + 1) != 2)
		{
			i++;
			var_name = get_var_name(i, line);
			i += (ft_strlen(var_name) - 1);
			if (!ft_strncmp(var_name, "?", 1))
				new_line = expand_last_exit(new_line, data->last_exit);
			else
				new_line = expand_single_var(new_line, var_name, temp_env);
			free(var_name);
		}
		else
			new_line = append_char(new_line, line[i++]); //check this
	}
	new_line = append_char(new_line, '\0');
	ft_free_tab(temp_env);
	return (new_line);
}
