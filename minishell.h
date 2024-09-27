#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FALSE 0
# define TRUE 1

int		what_quotes(char const *string);
char	**get_tokens(char *line);

typedef struct	s_cmd {
	char	*cmd;
	char	**options;
	char	**args;
	char	**env;
}		t_cmd;

#endif
