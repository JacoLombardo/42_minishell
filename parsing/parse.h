#include "../includes/minishell.h"

typedef enum	e_node_type
{
		PIPELINE,
		FULL_CMD,
		REDIRECT,
		SIMPLE_CMD,
}		t_node_type;

typedef enum	e_redir_type
{
		APPEND = T_APPEND,
		HEREDOC = T_HEREDOC,
		OUT = T_OUT,
		IN = T_IN,
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
	t_redir_type	type;
	char 			*target;
}		t_redirect;
