#include "../includes/minishell.h"

void	print_node(t_node *node)
{
	t_arg		*arg;
	t_redirect	*redir;
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

void	print_jacopo(t_cmd *jacopo)
{
	const char	*types[] = {"APPEND", "HEREDOC", "OUT", "IN", "ERROR"};
	
	printf("jacopo's command: %s\n", jacopo->cmd);
	printf("jacopo's args: ");
	int i = 0;
	while (jacopo->args[i])
	{
		printf("%s, ", jacopo->args[i]);
		i++;
	}
	printf("\n");
	printf("jacopo's targets: ");
	i = 0;
	while (jacopo->targets[i])
	{
		printf("%s, ", jacopo->targets[i]);
		i++;
	}
	printf("\n");
	printf("jacopo's redirection types: ");
	int j = i;
	while (i > 0)
	{
		printf("%s, ", types[jacopo->redir_types[j - i]]);
		i--;
	}
	printf("\n");
}
