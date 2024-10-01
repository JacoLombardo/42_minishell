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

typedef enum	e_type {
		THING,
		OPERATOR,
}		t_type;

typedef struct	s_token {
	t_type			type;
	char			*value;
	struct s_token	*next;
	struct s_token	*prev;
}		t_token;

typedef struct	s_cmd {
	char	*cmd;
	char	**options;
	char	**args;
	char	**env;
}		t_cmd;

int			what_quotes(char const *string);
char		**get_tokens(char *line);
void		append_token(t_token *token_list, char *value);
t_token		*find_first(t_token *token_list);
t_token		*tokenize(char **line);
void		free_token_list(t_token *current);
t_token		*new_token(char *value);

#endif
