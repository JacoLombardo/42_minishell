#include "parse.h"

void	advance(t_parser *parser)
{
	parser->curr_token = parser->curr_token->next;
}

int		accept(t_parser *parser, t_type type)
{
	if (parser->curr_token->type == type)
	{
		advance(parser);
		return (TRUE);
	}
	return (FALSE);
}

int		expect(t_parser *parser, t_type type)
{
	if (accept(parser, type))
		return (TRUE);
	parser->err_num = 1;
	// todo: write cleanup function
	return (FALSE);
}

t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;

	return (node);
}

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
	advance(parser);

	while (accept(parser, THING))
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
	return (node);

}

t_node	*make_redirect(t_parser *parser)
{
	t_redirect	*redir;
	t_node 		*node;

	redir = malloc(sizeof(t_redirect));
	redir->type = parser->curr_token->type;

	expect(parser, THING);
	redir->target = parser->curr_token->value;

	node = create_node(REDIRECT);
	node->redirect = redir;
	return (node);
}

t_node	*make_full_command(t_parser *parser)
{
	t_node	*redir_nodes;
	t_node	*cmd_node;
	t_node 	*node;

	if (parser->curr_token->type == THING)
	{
		cmd_node = make_simple_command(parser);
	}

	if (parser->curr_token->type >= T_APPEND)
	{
		redir_nodes = make_redirect(parser);
	}

	node = create_node(FULL_CMD);
	node->pair = malloc(sizeof(t_pair));
	node->pair->left = cmd_node;
	node->pair->right = redir_nodes;
	
	return (node);
}

t_node	*make_pipeline(t_parser *parser)
{

}
