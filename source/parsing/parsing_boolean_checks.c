/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_boolean_checks.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 11:19:50 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/24 11:19:53 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

int	is_builtin(char *cmd)
{
	int	len;

	if (!cmd)
		return (FALSE);
	len = ft_strlen(cmd);
	if (!ft_strncmp(cmd, "echo", len) || !ft_strncmp(cmd, "pwd", len))
		return (TRUE);
	else if (!ft_strncmp(cmd, "env", len) || !ft_strncmp(cmd, "cd", len))
		return (TRUE);
	else if (!ft_strncmp(cmd, "export", len) || !ft_strncmp(cmd, "unset", len))
		return (TRUE);
	else if (!ft_strncmp(cmd, "exit", len))
		return (TRUE);
	return (FALSE);
}

int	is_assignment(char *input)
{
	int	i;

	i = 0;
	if (!ft_strrchr(input, '='))
		return (FALSE);
	while (input[i])
	{
		if (input[i] == '=')
			break ;
		if (!is_bash_valid(input[i]))
			return (FALSE);
		i++;
	}
	return (TRUE);
}

int	is_bash_valid(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (TRUE);
	return (FALSE);
}

int	is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int	is_operator_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (TRUE);
	return (FALSE);
}
