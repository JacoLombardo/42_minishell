/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 17:31:21 by csilva-r          #+#    #+#             */
/*   Updated: 2024/10/24 17:31:26 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static int	is_bash_valid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

static char	*get_var_name(int i, char *line)
{
	int		var_name_len;
	char	*temp;
	char	*var_name;

	var_name_len = 0;
	while (is_bash_valid(line[i]))
	{
		var_name_len++;
		i++;
	}
	temp = ft_strjoin(ft_substr(line, i - var_name_len, var_name_len), "=");
	var_name = ft_strjoin(temp, "=");
	free(temp);
	return (var_name);
}

static char	*append_value(char *new_line, char *var_value, char *var_name)
{
	char	*temp;

	temp = ft_strdup(new_line);
	free(new_line);
	new_line = ft_strjoin(temp, var_value + ft_strlen(var_name) + 1);
	free(temp);
	free(var_name);
	free(var_value);
	return (new_line);
}

static char	*append_char(char *new_line, char c)
{
	char	*temp;

	temp = ft_strdup(new_line);
	free(new_line);
	new_line = ft_charjoin(temp, c);
	free(temp);
	return (new_line);
}

static char	*expand_single_var(char *new_line, char *var_name, char *env[])
{
	int		j;
	char	*var_value;

	j = 0;
	while (env[j])
	{
		var_value = ft_strnstr(env[j], var_name, ft_strlen(env[j]));
		if (var_value)
		{
			new_line = append_value(new_line, var_value, var_name);
			break ;
		}
		j++;
	}
	return (new_line);
}

char	*expand_vars(char *line, char *env[])
{
	int		i;
	char	*var_name;
	char	*new_line;

	i = 0;
	new_line = ft_strdup("");
	while (line[i])
	{
		if (line[i] == '$' && what_quotes(line + i + 1) != 2)
		{
			i++;
			var_name = get_var_name(i, line);
			new_line = expand_single_var(new_line, var_name, env);
		}
		new_line = append_char(new_line, line[i]);
		i++;
	}
	return (new_line);
}
