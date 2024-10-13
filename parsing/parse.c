#include "../includes/minishell.h"

t_parser	*parser_init(t_token *token_list)
{
	t_parser	*parser;

	parser = malloc(sizeof(t_parser));
	parser->err_num = 0;
	parser->curr_token = token_list;
	parser->node = NULL;
	return (parser);
}

/*	Jacopo:
	For now, you can call this function to return a t_cmd like we discussed.
	The struct is also signalled with comments in the header, check it out.
	"print_jacopo" prints it.
	None of this is taking pipelines into account, but this works for commands
	+ args + any number of redirections.
	Let me know how it goes.
*/
t_cmd	*parse(t_token *token_list)
{
	t_parser	*parser;
	t_node		*top_node;
	t_cmd		*jacopo;

	parser = parser_init(token_list);
	top_node = make_full_command(parser);
	//print_node(top_node);
	jacopo = jacopize(top_node);
	print_jacopo(jacopo);
	return(jacopo);
}
