#include "minishell.h"

t_token	*new_token(char *value, t_type type)
{
	t_token		*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->type = type;
	if (value != NULL)
		new_token->value = ft_strdup(value);
	else
		new_token->value = NULL;
	new_token->next = NULL;
	new_token->prev = NULL;
	return (new_token);
}

void	append_token(t_token *token_list, char *value, t_type type)
{
	t_token		*new;

	while (token_list->next != NULL)
		token_list = token_list->next;
	new = new_token(value, type);
	new->prev = token_list;
	token_list->next = new;
}

int		operator_token(t_token *token_list, char *line_pos)
{
	int		len;
	t_type	type;

	type = get_type(line_pos);
	append_token(token_list, NULL, type);
	if (type == T_PIPE || type == T_BIG || type == T_SMALL)
		len = 1;
	else
		len = 2;
	return (len);
}

int		value_token(t_token *token_list, char *line_pos)
{
	char	*value;
	int		len;
	int		start;

	start = 0;
	len = 0;
	// skip spaces
	while (line_pos[start] == ' ')
		start++;
	// extract value (handle quotes)
	while (!((is_operator_char(line_pos[len]) || line_pos[len] == ' ') && !what_quotes(line_pos + len + 1)) && line_pos[len])
		len++;
	value = ft_substr(line_pos, start, len);
	append_token(token_list, value, THING);
	return (len);
}
