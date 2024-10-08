#include "../includes/minishell.h"


int		is_operator_char(char c)
{
	// problem here with &. this will also catch a single one, which means nothing.
	// for & i only care when its 2
	if (c == '|' || c == '>' || c == '<' || c == '&')
		return (TRUE);
	return (FALSE);
}

t_token *tokenize(char *line)
{
	t_token *token_list;
	t_token	*dummy_first;
	int		len;

	token_list = malloc(sizeof(t_token));
	token_list->next = NULL;
	token_list->prev = NULL;
	int i = 0;
	while(*line)
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
