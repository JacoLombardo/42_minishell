#include "../includes/minishell.h"

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

// if what_quotes returns 1 or 2 the string has unclosed quotes and is invalid.
// how does it work as is? i need to know what closed quotes are superior and effective, also when they are closed, to determine how to handle $
