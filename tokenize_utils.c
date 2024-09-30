#include "minishell.h"

t_type		get_type(char *str)
{
	if (ft_strncmp(str, "||", ft_strlen(str))
			|| ft_strncmp(str, "&&", ft_strlen(str))
			|| ft_strncmp(str, "|", ft_strlen(str))
			|| ft_strncmp(str, ">", ft_strlen(str))
			|| ft_strncmp(str, ">>", ft_strlen(str))
			|| ft_strncmp(str, "<", ft_strlen(str))
			|| ft_strncmp(str, "<<", ft_strlen(str)))
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
	new_token->value = value;
	new_token->next = NULL;
	return (new_token);
}

void	append_token(t_token *token_list, char *value)
{
	t_token		*new;

	while (token_list->next)
		token_list = token_list->next;
	new = new_token(value);
	token_list->next = new;
}
