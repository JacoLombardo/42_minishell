#include "../includes/minishell.h"

t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;

	return (node);
}

void	advance(t_parser *parser)
{
	parser->curr_token = parser->curr_token->next;
}

int		accept(t_parser *parser, t_type type)
{
	if (parser->curr_token->next && parser->curr_token->next->type == type)
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

t_type	peek(t_parser *parser)
{
	if (parser->curr_token)
		return (parser->curr_token->type);

	return (-1);
}
