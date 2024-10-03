#include "minishell.h"

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
	char	*line2 =  ft_strdup("hello i || >> am < $USER > and this is $FRIEND"); // quotes no spaces. 3
	char	*line3 = ft_strdup("hola como estas");
	char	*line6;
	char	*test;
	int		i = 0;
	t_token *token_list;

	line6 = expand_vars(line2, env);
	free(line2);
	tokenize(line6);
	//while (token_list->next != NULL)
	//{
	//	print_ttoken(token_list);
	//	token_list = token_list->next;
	//}
	//print_ttoken(token_list);
//
	//free(line6);
	//free_token_list(find_first(token_list));

	test = ft_charjoin(line6, '!');
	printf("%s\n", test);

	return (0);
}
