#ifndef MINISHELL_H
# define MINISHELL_H

# include "includes/libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FALSE 0
# define TRUE 1

int		what_quotes(char const *string);
char	**get_tokens(char *line);

typedef enum	e_type {
		THING,
		OPERATOR,
}		t_type;

typedef struct	s_token {
	t_type		type;
	char	*value;
	t_token	*next;
}		t_token;

typedef struct	s_cmd {
	char	*cmd;
	char	**options;
	char	**args;
	char	**env;
}		t_cmd;

#endif
