/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:18:24 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/06 15:54:28 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

static void	cleanup_args(t_arg *arg)
{
	if (!arg)
		return ;
	if (arg->value)
		free(arg->value);
	cleanup_args(arg->next);
	free(arg);
}

static void	cleanup_redirs(t_redirect *redir)
{
	if (!redir)
		return ;
	if (redir->target)
		free(redir->target);
	cleanup_redirs(redir->next);
	free(redir);
}

void	cleanup_nodes(t_node *top_node)
{
	if (!top_node)
		return ;
	if (top_node->type == PIPELINE || top_node->type == FULL_CMD)
	{
		cleanup_nodes(top_node->pair->left);
		cleanup_nodes(top_node->pair->right);
		free(top_node->pair);
	}
	else if (top_node->type == SIMPLE_CMD)
	{
		free(top_node->simp_cmd->command);
		cleanup_args(top_node->simp_cmd->arg);
		free(top_node->simp_cmd);
	}
	else if (top_node->type == REDIRECT)
		cleanup_redirs(top_node->redirect);
	free(top_node);
}
