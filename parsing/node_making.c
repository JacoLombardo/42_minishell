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

	redir_nodes = NULL;
	cmd_node = NULL;
	if (peek(parser) == THING)
	{
		cmd_node = make_simple_command(parser);
		advance(parser);
	}
	if (peek(parser) >= T_APPEND)
	{
		redir_nodes = make_redirect(parser);
		advance(parser);
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
