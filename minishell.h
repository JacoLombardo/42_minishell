/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 15:31:28 by jalombar         ###   ########.fr       */
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

#endif