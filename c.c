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
	//char	*line2 =  ft_strdup("echo hello");
	char	*line6;

	t_token *token_list;

	if (!argc)
		printf("bup");
	line6 = expand_vars(argv[1], env);
	//free(line2);
	token_list = tokenize(line6);
	free(line6);

	parse(find_first(token_list));
	free_token_list(find_first(token_list));

	return (0);
}
