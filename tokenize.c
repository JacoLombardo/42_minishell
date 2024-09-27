#include "minishell.h"

int	count_tokens(char const *s)
{
	int	count;
	int	i;
	int	check;

	if (!s)
		return (1);
	i = 0;
	count = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] != ' ' && check == 0 && what_quotes(s + i + 1) == 0)
		{
			count++;
			check = 1;
		}
		else if (s[i] == ' ')
			check = 0;
		i++;
	}
	return (count);
}

static int	find_index(char const *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == ' ' && what_quotes(s + i + 1) == 0)
			return (i);
		i++;
	}
	return (i);
}

static char	**free_and_return_null(char **new)
{
	int	i;

	i = 0;
	while (new[i] != NULL)
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

char	**get_tokens(char *line)
{
	char	**tokens;
	int		i;
	int		cut_from;
	int		cut_to;

	tokens = (char **)malloc(sizeof(char *) * (count_tokens(line) + 1));
	if (!tokens || !line)
		return (NULL);

	i = 0;
	cut_from = 0;
	while (i < count_tokens(line))
	{
		while (line[cut_from] == ' ')
			cut_from++;
		cut_to = find_index(line + cut_from); //// 
		tokens[i] = (char *)malloc(sizeof(char) * (cut_to + 1));
		if (!tokens[i])
			return (free_and_return_null(tokens));
		ft_strlcpy(tokens[i], line + cut_from, cut_to + 1);
		cut_from += cut_to + 1;
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}
