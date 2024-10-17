#include "minishell.h"

int	main2(int argc, char **argv, char **env)
{
	char	*line;
	t_full_cmd	*full_cmd;

	if (!argc && !argv && !env)
		return (1);
	line = ft_strdup(argv[1]);
	full_cmd = parse(line, env);
	print_jacopo(full_cmd, 0);
	return (0);
}
