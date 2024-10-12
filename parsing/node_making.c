#include "../includes/minishell.h"

t_node	*make_simple_command(t_parser *parser)
{
	t_simple_cmd	*simple;
	t_node 			*node;
	t_arg			*new;
	t_arg			*curr;

	simple = malloc(sizeof(t_simple_cmd));
	simple->command = parser->curr_token->value;
	simple->arg = malloc(sizeof(t_arg));
	simple->arg->next = NULL;
	simple->arg->value = NULL;
	while (accept(parser, T_THING))
	{
		curr = simple->arg;
		while (curr->next)
			curr = curr->next;
		new = malloc(sizeof(t_arg));
		new->value = parser->curr_token->value;
		new->next = NULL;
		curr->next = new;
	}
	node = create_node(SIMPLE_CMD);
	node->cmd = simple;
	advance(parser);
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

t_node	*make_redirect(t_parser *parser, t_redirect *redir_list)
{
	t_node 		*node;

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
	redir->target = parser->curr_token->value;
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
	//
	redir_list = malloc(sizeof(t_redirect));
	redir_list->type = R_ERR;
	redir_list->target = NULL;
	redir_list->next = NULL;
	//
	if (peek(parser) == T_THING)
		node->pair->left = make_simple_command(parser);
	while (peek(parser) >= T_APPEND)
		append_redirect(parser, redir_list);
	node->pair->right = make_redirect(parser, redir_list);
	return (node);
}

t_node	*make_pipeline(t_parser *parser)
{

}
