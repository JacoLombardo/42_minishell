#include "includes/minishell.h"

void	print_ttoken(t_token *token)
{
	printf("value: %s\ttype: %i. ", token->value, token->type);
	if (!token->next)
		printf("this is the last one");
	printf("\n");
}

int		is_quote(char c)
{
	if (c == '\'' || c == '\"')
		return (TRUE);
	return (FALSE);
}

int	main(int argc, char *argv[], char *env[])
{
	char	*line;

	if (argc != 2)
	{
		printf("pass the whole thing as a single string for now\n");
		return (1);
	}
	line = ft_strdup(argv[1]);
	parse(line, env);
	return (0);
}
