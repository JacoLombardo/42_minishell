/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 19:22:03 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include "includes/execution.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>

# define FALSE 0
# define TRUE 1

static int			g_program = 1;

typedef struct s_data
{
	char			**env;
	HIST_ENTRY		**history;
	int				last_exit;
	struct s_ast	*ast;
}					t_data;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			**redirections;
	char			**targets;
    char            *operator;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ast
{
	struct s_cmd	**cmds;
	char			**operators;
}					t_ast;

/* Carolina */
typedef struct	s_redirect
{
	t_redir_type		type;
	char 				*target;
	struct s_redirect	*next;
}		t_redirect;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	t_redir_type	*redir_types;
	char			**targets;
}		t_cmd;

/* testing */
void	print_node(t_node *node);
void	print_jacopo(t_cmd *jacopo);

#endif