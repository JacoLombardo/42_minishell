#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FALSE 0
# define TRUE 1

typedef enum	e_type {
		THING,
		T_OR,
		T_AND,
		T_BIGBIG, // >>
		T_SMALLSMALL, // <<
		T_PIPE,
		T_BIG,
		T_SMALL,
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


//expanding
char		*expand_vars(char *line, char *env[]);
// tokenizing
t_token		*tokenize(char *line);
// making + appending
t_token		*new_token(char *value, t_type type);
void		append_token(t_token *token_list, char *value, t_type type);
int			operator_token(t_token *token_list, char *line_pos);
int			value_token(t_token *token_list, char *line_pos);
// utilities
t_type		get_type(char *str);
t_token		*find_first(t_token *token_list);
void		free_token_list(t_token *current);
int			what_quotes(char const *string);
int			is_operator_char(char c);

char		*ft_charjoin(char const *str, char const c);

#endif
