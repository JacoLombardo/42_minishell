#include "../includes/minishell.h"

t_type		get_type(char *str)
{
	if (ft_strncmp(str, "||", 2) == 0)
		return (T_OR);
	else if (ft_strncmp(str, "&&", 2) == 0)
		return (T_AND);
	else if (ft_strncmp(str, ">>", 2) == 0)
		return (T_BIGBIG);
	else if (ft_strncmp(str, "<<", 2) == 0)
		return (T_SMALLSMALL);
	else if (ft_strncmp(str, "|", 1) == 0)
		return (T_PIPE);
	else if (ft_strncmp(str, ">", 1) == 0)
		return (T_BIG);
	else if (ft_strncmp(str, "<", 1) == 0)
		return (T_SMALL);
	return (THING);
}

int		what_quotes(char const *string)
{
	int i = 0;
	int quote_type = 0;

	while (string[i])
	{
		if (string[i] == '\"' && quote_type == 0)
			quote_type = 1;
		else if (string[i] == '\"' && quote_type == 1)
			quote_type = 0;
		else if (string[i] == '\'' && quote_type == 0)
			quote_type = 2;
		else if (string[i] == '\'' && quote_type == 2)
			quote_type = 0;
		i++;
	}
	return (quote_type);
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
