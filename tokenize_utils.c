#include "minishell.h"

t_type		get_type(char *str)
{
	if (ft_strncmp(str, "||", ft_strlen(str)) == 0
			|| ft_strncmp(str, "&&", ft_strlen(str)) == 0
			|| ft_strncmp(str, "|", ft_strlen(str)) == 0
			|| ft_strncmp(str, ">", ft_strlen(str)) == 0
			|| ft_strncmp(str, ">>", ft_strlen(str)) == 0
			|| ft_strncmp(str, "<", ft_strlen(str)) == 0
			|| ft_strncmp(str, "<<", ft_strlen(str)) == 0)
		return OPERATOR;
	return (THING);
}

t_token	*new_token(char *value)
{
	t_token		*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = get_type(value);
	new_token->value = ft_strdup(value);
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	append_token(t_token *token_list, char *value)
{
	t_token		*new;

	while (token_list->next != NULL)
		token_list = token_list->next;
	new = new_token(value);
	new->prev = token_list;
	token_list->next = new;
}

t_token	*find_first(t_token *token_list)
{
	while (token_list->prev != NULL)
		token_list = token_list->prev;
	return (token_list);
}

void	free_token_list(t_token *current)
{
	t_token *next;

	next = current;
	while (next)
	{
		free(current->value);
		next = current->next;
		free(current);
		current = next;
	}
}
