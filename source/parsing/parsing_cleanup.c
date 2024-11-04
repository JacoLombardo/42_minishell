/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cleanup.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:18:24 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/04 18:18:28 by csilva-r         ###   ########.fr       */
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

void	cleanup_string_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

void	cleanup_jacopo(t_full_cmd *jacopo)
{
	int	i;

	if (!jacopo)
		return ;
	if (jacopo->cmd)
		free(jacopo->cmd);
	cleanup_string_array(jacopo->args);
	if (jacopo->redirections)
		free(jacopo->redirections);
	cleanup_string_array(jacopo->targets);
	if (jacopo->operator)
		free(jacopo->operator);
	cleanup_jacopo(jacopo->next);
	free(jacopo);
}
