/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:22 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 10:26:43 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_redirect	*find_last(t_redirect *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
	return (node);
}

t_redir_type	get_redirect_type(t_type token_type)
{
	if (token_type == T_APPEND)
		return (R_APPEND);
	else if (token_type == T_HEREDOC)
		return (R_HEREDOC);
	else if (token_type == T_IN)
		return (R_IN);
	else if (token_type == T_OUT)
		return (R_OUT);
	else
		return (R_ERR);
}

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
