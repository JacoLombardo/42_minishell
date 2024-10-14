/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 19:15:00 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 19:34:15 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../minishell.h"

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

t_cmd		*parse(char *line, char *env[]);

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

char	**args_to_array(t_arg *arg_list);
void	redir_to_arrays(t_cmd *jacopo, t_redirect *redir_list);
t_cmd	*jacopize(t_node *full_cmd);

/* utilities */
t_type		get_type(char *str);
t_token		*find_first(t_token *token_list);
void		free_token_list(t_token *current);
int			what_quotes(char const *string);
int			is_operator_char(char c);

#endif