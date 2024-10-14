#include "../includes/minishell.h"

t_redirect	*find_last(t_redirect *redir)
{
	if (!redir)
		return (NULL);
	while (redir->next)
		redir = redir->next;
	return (redir);
}

t_node	*create_node(t_node_type type)
{
	t_node	*node;

	node = malloc(sizeof(t_node));
	node->type = type;
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
