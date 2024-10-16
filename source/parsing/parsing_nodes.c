/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_nodes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:32:10 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 10:26:25 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

t_node	*make_simple_command(t_parser *parser)
{
	t_simple_cmd	*simple;
	t_node			*node;
	t_arg			*new;
	t_arg			*curr;

	simple = malloc(sizeof(t_simple_cmd));
	simple->command = ft_strdup(parser->curr_token->value);
	simple->arg = malloc(sizeof(t_arg));
	simple->arg->next = NULL;
	simple->arg->value = NULL;
	while (accept(parser, T_THING))
	{
		curr = simple->arg;
		while (curr->next)
			curr = curr->next;
		new = malloc(sizeof(t_arg));
		new->value = ft_strdup(parser->curr_token->value);
		new->next = NULL;
		curr->next = new;
	}
	node = create_node(SIMPLE_CMD);
	node->simp_cmd = simple;
	advance(parser);
	return (node);
}

t_node	*make_redirect(t_redirect *redir_list)
{
	t_node	*node;

	node = create_node(REDIRECT);
	node->redirect = redir_list;
	return (node);
}

void	append_redirect(t_parser *parser, t_redirect *redir_list)
{
	t_redirect	*redir;

	redir = malloc(sizeof(t_redirect));
	redir->type = get_redirect_type(parser->curr_token->type);
	redir->next = NULL;
	expect(parser, T_THING);
	redir->target = ft_strdup(parser->curr_token->value);
	find_last(redir_list)->next = redir;
	advance(parser);
}

t_node	*make_full_command(t_parser *parser)
{
	t_node		*node;
	t_redirect	*redir_list;

	node = create_node(FULL_CMD);
	node->pair = malloc(sizeof(t_pair));
	node->pair->left = NULL;
	node->pair->right = NULL;
	redir_list = malloc(sizeof(t_redirect));
	redir_list->type = R_ERR;
	redir_list->target = NULL;
	redir_list->next = NULL;
	while (peek(parser) >= T_APPEND)
		append_redirect(parser, redir_list);
	if (peek(parser) == T_THING)
		node->pair->left = make_simple_command(parser);
	while (peek(parser) >= T_APPEND)
		append_redirect(parser, redir_list);
	node->pair->right = make_redirect(redir_list);
	return (node);
}

t_node	*make_pipeline(t_parser *parser)
{
	t_node	*pipeline;

	pipeline = create_node(PIPELINE);
	pipeline->pair = malloc(sizeof(t_pair));
	pipeline->pair->right = NULL;
	pipeline->pair->left = make_full_command(parser);
	if (peek(parser) == T_PIPE)
	{
		advance(parser);
		pipeline->pair->right = make_pipeline(parser);
	}
	return (pipeline);
}
