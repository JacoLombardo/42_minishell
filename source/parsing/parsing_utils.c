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

t_arg	*find_last_arg(t_arg *arg)
{
	if (!arg)
		return (NULL);
	while (arg->next)
		arg = arg->next;
	return (arg);
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
