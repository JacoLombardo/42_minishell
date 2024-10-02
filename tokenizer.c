#include "minishell.h"

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
	int		len;

	while(*line)
	{
		while (*line == ' ')
			line++;
		if (is_operator_char(*line))
			line += operator_token(token_list, line);
		else
			line += value_token(token_list, line);
	}
}
