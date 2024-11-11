#include "../../includes/parsing.h"

int	what_quotes(char const *string)
{
	int	i;
	int	quote_type;

	i = 0;
	quote_type = 0;
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

static int		to_remove(char *line, int i)
{
	if (!is_quote(line[i]))
		return (FALSE);
	else if (!what_quotes(line + i))
		return (TRUE);
	else if (what_quotes(line + i) && !what_quotes(line + i + 1))
		return (TRUE);
	else
		return (FALSE);
}

char	*super_trimmer(char *line)
{
	char	*trimmed;
	char	*temp;

	trimmed = ft_strdup("");
	int		i = 0;
	while (line[i])
	{
		if (!to_remove(line, i))
		{
			temp = ft_strdup(trimmed);
			free(trimmed);
			trimmed = ft_charjoin(temp, line[i]);
			free(temp);
		}
		i++;
	}
	return(trimmed);
}

char	*trim_quote(char *str)
{
	char	*trimmed;

	if (!str)
		return (NULL);
	if (what_quotes(str + 1))
		trimmed = ft_substr(str, 1, ft_strlen(str) - 2);
	else
		trimmed = ft_strdup(str);
	return (trimmed);
}
