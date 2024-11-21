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

t_node	*make_simple_command(t_parser *parser, t_redirect *redir_list)
{
	t_simple_cmd	*simple;
	t_node			*node;
	t_arg			*new;
	t_arg			*curr;

	simple = malloc(sizeof(t_simple_cmd));
	simple->command = ft_strdup(parser->curr_token->value);
	simple->arg = ft_calloc(1, sizeof(t_arg));
	while (accept(parser, T_THING) || accept_redirect(parser))
	{
		if (peek(parser) >= T_APPEND)
			append_redirect(parser, redir_list);
		else
		{
			curr = simple->arg;
			while (curr->next)
				curr = curr->next;
			new = ft_calloc(1, sizeof(t_arg));
			new->value = ft_strdup(parser->curr_token->value);
			curr->next = new;
		}
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
	int			exp_heredoc;

	exp_heredoc = TRUE;
	redir = malloc(sizeof(t_redirect));
	redir->type = get_redirect_type(parser->curr_token->type);
	redir->next = NULL;
	if (!expect(parser, T_THING))
	{
		redir->target = NULL;
		return ;
	}
	redir->target = ft_strdup(parser->curr_token->value);
	if (redir->type == R_HEREDOC)
	{
		if (redir->target[0] == '\'' || redir->target[0] == '\"')
			exp_heredoc = FALSE;
		ft_heredoc(redir->target, parser->data, exp_heredoc);
	}
	find_last(redir_list)->next = redir;
}

t_node	*make_full_command(t_parser *parser)
{
	t_node		*node;
	t_redirect	*redir_list;

	node = create_node(FULL_CMD);
	node->pair = ft_calloc(1, sizeof(t_node));
	redir_list = ft_calloc(1, sizeof(t_redirect));
	redir_list->type = R_ERR;
	while (peek(parser) >= T_APPEND)
	{
		append_redirect(parser, redir_list);
		advance(parser);
	}
	while (peek(parser) == T_THING)
	{
		if (is_assignment(parser->curr_token->value))
		{
			ft_var_to_temp(parser->curr_token->value, parser->data);
			advance(parser);
			continue ;
		}
		node->pair->left = make_simple_command(parser, redir_list);
		break ;
	}
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
