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

void	print_node(t_node *node)
{
	t_arg	*arg;
	t_redirect *redir;
	const char	*types[] = {"APPEND", "HEREDOC", "OUT", "IN", "ERROR"};

	if (!node)
		return ;
	if (node->type == PIPELINE)
	{
		printf("\npipeline: ");
		print_node(node->pair->left);
		print_node(node->pair->right);
	}
	else if (node->type == FULL_CMD)
	{
		printf("\n\tfull command: ");
		print_node(node->pair->left);
		print_node(node->pair->right);
	}
	else if (node->type == REDIRECT)
	{
		printf("\n\t\tredirects: ");
		redir = node->redirect;
		while (redir->next)
		{
			redir = redir->next;
			printf("| %s, target %s ", types[redir->type], redir->target);
		}
	}
	else if (node->type == SIMPLE_CMD)
	{
		printf("\n\t\tsimple_command: ");
		printf("cmd %s, args: ", node->cmd->command);
		arg = node->cmd->arg;
		while (arg->next)
		{
			arg = arg->next;
			printf("%s, ", arg->value);
		}
	}
	else
		printf ("?");
	printf("\n");
}

void	parse(t_token *token_list)
{
	t_parser	*parser;
	t_node		*top_node;

	parser = parser_init(token_list);
	top_node = make_full_command(parser);

	print_node(top_node);
}
