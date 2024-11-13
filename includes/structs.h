/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:47:39 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/13 15:55:29 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>

/* DATA */
typedef struct s_data
{
	int						shell_id;
	char					**env;
	HIST_ENTRY				**history;
	int						last_exit;
}							t_data;

/* PARSING */
typedef struct s_node
{
	t_node_type				type;
	union
	{
		struct s_pair		*pair;
		struct s_simple_cmd	*simp_cmd;
		struct s_redirect	*redirect;
	};
}							t_node;

typedef struct s_token
{
	t_type					type;
	char					*value;
	struct s_token			*next;
	struct s_token			*prev;
}							t_token;

typedef struct s_parser
{
	int						err_num;
	t_data					*data;
	t_token					*curr_token;
	t_node					*node;
}							t_parser;

typedef struct s_pair
{
	t_node					*left;
	t_node					*right;
}							t_pair;

typedef struct s_arg
{
	char					*value;
	struct s_arg			*next;
}							t_arg;

typedef struct s_simple_cmd
{
	char					*command;
	t_arg					*arg;
}							t_simple_cmd;

typedef struct s_redirect
{
	t_redir_type			type;
	char					*target;
	struct s_redirect		*next;
}							t_redirect;

/* EXECUTION */
typedef struct s_pipe
{
	int						*prev_fd;
	pid_t					pid;
	int						pipe_fd[2];
}							t_pipe;

typedef struct s_full_cmd
{
	int						built_in;
	char					*cmd;
	char					**args;
	t_redir_type			*redirections;
	char					**targets;
	char					*operator;
	struct s_full_cmd		*next;
}							t_full_cmd;

#endif
