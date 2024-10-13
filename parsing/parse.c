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

char	**args_to_array(t_arg *arg_list)
{
	char	**result;
	int		arg_count;
	t_arg	*first;

	arg_count = 0;
	first = arg_list;
	while (arg_list->next)
	{
		arg_count++;
		arg_list = arg_list->next;
	}
	result = malloc(sizeof(char*) * (arg_count + 2));
	arg_count = 1;
	while (first->next)
	{
		first = first->next;
		result[arg_count] = ft_strdup(first->value);
		arg_count++;
	}
	result[arg_count] = NULL;
	return (result);
}

void	redir_to_arrays(t_cmd *jacopo, t_redirect *redir_list)
{
	t_redirect		*first;
	int				count;

	count = 0;
	first = redir_list;
	while (redir_list->next)
	{
		count++;
		redir_list = redir_list->next;
	}
	jacopo->redir_types = malloc(sizeof(t_redir_type) * count);
	jacopo->targets = malloc(sizeof(char*) * (count + 1));
	count = 0;
	while (first->next)
	{
		first = first->next;
		jacopo->redir_types[count] = first->type;
		jacopo->targets[count] = ft_strdup(first->target);
		count++;
	}
	jacopo->targets[count] = NULL;
}

t_cmd	*convert_full_cmd(t_node *full_cmd)
{
	t_cmd	*jacopo;

	jacopo = malloc(sizeof(t_cmd));
	if (!jacopo)
		return (NULL);
	jacopo->cmd = ft_strdup(full_cmd->pair->left->cmd->command);
	jacopo->args = args_to_array(full_cmd->pair->left->cmd->arg);
	jacopo->args[0] = ft_strdup(jacopo->cmd);
	jacopo->redir_types = NULL;
	jacopo->targets = NULL;
	redir_to_arrays(jacopo, full_cmd->pair->right->redirect);
	
	return (jacopo);
}

void	parse(t_token *token_list)
{
	t_parser	*parser;
	t_node		*top_node;
	t_cmd		*jacopo;

	parser = parser_init(token_list);
	top_node = make_full_command(parser);
	print_node(top_node);
	jacopo = convert_full_cmd(top_node);
	print_jacopo(jacopo);
}
