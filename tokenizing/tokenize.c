#include "../includes/minishell.h"

int	is_operator_char(char c)
{
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (TRUE);
	return (FALSE);
}

t_token	*tokenize(char *line)
{
	t_token	*token_list;
	t_token	*dummy_first;
	int		i;

	token_list = malloc(sizeof(t_token));
	token_list->next = NULL;
	token_list->prev = NULL;
	i = 0;
	while (*line)
	{
		while (*line == ' ')
			line++;
		if (is_operator_char(*line))
			line += operator_token(token_list, line);
		else
			line += value_token(token_list, line);
		i++;
	}
	dummy_first = find_first(token_list);
	token_list = dummy_first->next;
	token_list->prev = NULL;
	free(dummy_first);
	return (token_list);
}
