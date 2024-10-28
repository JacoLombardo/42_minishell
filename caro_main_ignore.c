#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	//char	*line;
	//t_full_cmd	*full_cmd;

	if (!argc && !argv && !env)
		return (1);

	printf("%s\n", expand_vars(argv[1], env));
	//line = ft_strdup(argv[1]);
	//full_cmd = parse(line, env);
	return (0);
}
