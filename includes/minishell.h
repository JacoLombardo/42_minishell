#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
//# include "parse.h"

# include <readline/readline.h>
# include <readline/history.h>

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>

# define FALSE 0
# define TRUE 1

typedef enum	e_type {
		T_ERR,
		T_THING,
		T_PIPE,
		T_OR,
		T_AND,
		T_APPEND, // >>
		T_HEREDOC, // <<
		T_OUT,
		T_IN,
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

//expanding
int			what_quotes(char const *string);
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


// parse.h FIX!!!
typedef enum	e_node_type
{
		PIPELINE,
		FULL_CMD,
		REDIRECT,
		SIMPLE_CMD,
}		t_node_type;

typedef enum	e_redir_type
{
		R_APPEND,
		R_HEREDOC,
		R_OUT,
		R_IN,
		R_ERR,
}		t_redir_type;

typedef struct	s_node
{
	t_node_type		type;
	union
	{
		struct s_pair		*pair;
		struct s_simple_cmd	*cmd;
		struct s_redirect	*redirect;
	};
}		t_node;

typedef struct	s_parser
{
	int		err_num;
	t_token	*curr_token;
	t_node	*node;
}		t_parser;

typedef	struct	s_pair
{
	t_node	*left;
	t_node	*right;
}		t_pair;

typedef struct	s_arg
{
	char			*value;
	struct s_arg	*next;
}		t_arg;

typedef struct	s_simple_cmd
{
	char	*command;
	t_arg	*arg;
}		t_simple_cmd;

typedef struct	s_redirect
{
	t_redir_type		type;
	char 				*target;
	struct s_redirect	*next;
}		t_redirect;

void		parse(t_token *token_list);

t_node		*make_pipeline(t_parser *parser);
t_node		*make_full_command(t_parser *parser);
t_node		*make_redirect(t_redirect *redir_list);
void		append_redirect(t_parser *parser, t_redirect *redir_list);
t_redir_type	get_redirect_type(t_type token_type);
t_node		*make_simple_command(t_parser *parser);

t_redirect	*find_last(t_redirect *redir);
t_node		*create_node(t_node_type type);
void		advance(t_parser *parser);
int			accept(t_parser *parser, t_type type);
int			expect(t_parser *parser, t_type type);
t_type		peek(t_parser *parser);

#endif
