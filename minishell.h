/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/09 16:22:04 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
//# include <signal.h>
//# include <asm-generic/siginfo.h>

// static int			g_program;

typedef struct s_pipe
{
	int				*prev_fd;
	pid_t			pid;
	int				pipe_fd[2];
}					t_pipe;

typedef struct s_data
{
	char			**env;
	HIST_ENTRY		**history;
	int				last_exit;
}					t_data;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	char			*redirection;
	char			*target;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_ast
{
	struct s_cmd	**cmds;
	char			**operators;
	char			*input;
}					t_ast;

/* builtins */
int					ft_echo(t_cmd *cmd, t_data *data);
int					ft_pwd(t_cmd *cmd, t_data *data);
int					ft_env(t_cmd *cmd, t_data *data);

/* builtins2 */
int					ft_cd(t_cmd *cmd, t_data *data);
int					ft_export(t_cmd *cmd, t_data *data);
int					ft_unset(t_cmd *cmd, t_data *data);
int					ft_exit(t_cmd *cmd, t_data *data);

/* env */
char				**ft_deallocenv(char **env, int size, char *name);
char				**ft_reallocenv(char **env, int size);
char				**ft_cpyenv(char **env);
char				*ft_getenv(char *name, char **env);
char				*ft_setenv(char *name, char *value, char **env);

/* exec */
char				*ft_get_path(char *cmd, char **env);
int					ft_external(t_cmd *cmd, t_data *data);
int					ft_exec(t_cmd *cmd, t_data *data);
int					ft_check_operators(t_ast *ast, t_data *data);

/* operators */
int					ft_logical_and(t_cmd **cmd, t_data *data,
						char ***operators);
void				ft_logical_or(t_cmd **cmd, t_data *data, char ***operators);

/* pipe */
void				ft_child(t_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int					ft_parent(t_cmd *cmd, t_data *data, t_pipe pipex);
int					ft_fork(t_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int					ft_pipe(t_cmd **cmd, t_data *data, int count);

/* redirections */
void				ft_redirect(char *file, char *redirection);
void				ft_reset_redirect(char *file, char *redirection);

/* utils */
int					ft_tablen(char **tab);
char				*ft_free_tab(char **tab);
char				*ft_free_cmd(t_cmd *cmd);
char				*ft_free_ast(t_ast *ast);
int					ft_find_var(char *env, char *name);

#endif