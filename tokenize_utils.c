#include "minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token		*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token **token_list, char *value, t_type type)
{
	t_token		*current;
	t_token		*new;

	while (current->next)
		current = current->next;
	new = new_token(value, type);
	current->next = new;
}
