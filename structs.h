

# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_status
{
	char			*cmd; //original input string
	int				exit_status;
	struct s_status	*next;
}					t_status;

typedef struct s_data
{
	char			**env;
	HIST_ENTRY		**history;
	struct s_status	**ex_stat; // this may not be necessary. we could also store only the last one?
}					t_data;

typedef struct s_cmd
{
	char			*cmd; // pointer for the first array of the args, no need to have a copy
	char			**args; //options and then args
	char			*redirection; // redirection type ("<", ">", "<<", or ">>")
	char			*target; // redirection target
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ast
{
	struct s_cmd	**cmds;
	char			**operators;
	char			*input; // original string received as input, to be stored both as history and in the exit statuses array
}					t_ast;