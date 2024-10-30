#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	//char	*line;
	//t_full_cmd	*full_cmd;

	if (!argc && !argv && !env)
		return (1);

	// t_token	*token_list;

	// token_list = tokenize(argv[1]);
	// while (token_list)
	// {
	// 	print_ttoken(token_list);
	// 	token_list = token_list->next;
	// }
	//ft_heredoc("EOF", env, 1);

	printf("%s\n", expand_vars("hola $USER", env));
	printf("%s\n", expand_vars("hola $USER soy $FRIEND", env));

	//line = ft_strdup(argv[1]);
	//full_cmd = parse(line, env);
	return (0);
}
