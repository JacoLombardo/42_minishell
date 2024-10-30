#include "minishell.h"

int	main2(int argc, char **argv, char **env)
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
	ft_heredoc("EOF", env, 0);

	//line = expand_vars("hola $PEPITO", env);
	//printf("%s\n", line);
	//free(line);
	//line = expand_vars("hola $USER soy $FRIEND", env);
	//printf("%s\n", line);
	//free(line);
	//line = expand_vars("$PATH is the path", env);
	//printf("%s\n", line);
	//free(line);

	//line = ft_strdup(argv[1]);
	//full_cmd = parse(line, env);
	return (0);
}
