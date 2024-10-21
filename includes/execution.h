/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:48:35 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/17 18:21:09 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "../minishell.h"
# include "structs.h"
# include "types.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>

/* builtins */
int		ft_echo(t_full_cmd *cmd, t_data *data);
int		ft_pwd(t_full_cmd *cmd, t_data *data);
int		ft_env(t_full_cmd *cmd, t_data *data);

/* builtins2 */
int		ft_cd(t_full_cmd *cmd, t_data *data);
int		ft_export(t_full_cmd *cmd, t_data *data);
int		ft_unset(t_full_cmd *cmd, t_data *data);
void	ft_exit(int status, t_data *data);

/* env */
char	**ft_deallocenv(char **env, int size, char *name);
char	**ft_reallocenv(char **env, int size);
char	**ft_cpyenv(char **env);
char	*ft_getenv(char *name, char **env);
char	*ft_setenv(char *name, char *value, char **env);

/* exec */
char	*ft_get_path(char *cmd, char **env);
int		ft_external(t_full_cmd *cmd, t_data *data);
int		ft_exec(t_full_cmd *cmd, t_data *data);
int		ft_check_operators(t_ast *ast, t_data *data);

/* free */
int		ft_free_tab(char **tab);
int		ft_free_cmd(t_full_cmd *cmd);
int		ft_free_ast(t_ast *ast);
int		ft_free_data(t_data *data);

/* operators */
void	ft_skip_pipe(t_full_cmd **cmd, t_data *data, char ***operators);
int		ft_handle_pipe(t_full_cmd **cmd, t_data *data, char ***operators);
int		ft_logical_and(t_full_cmd **cmd, t_data *data, char ***operators,
			int status);
int		ft_logical_or(t_full_cmd **cmd, t_data *data, char ***operators,
			int status);

int		ft_check_operators2(t_full_cmd *cmd, t_data *data);
int		ft_pipe2(t_full_cmd **cmd, t_data *data, int count);
void	ft_skip_pipe2(t_full_cmd **cmd, t_data *data);
int		ft_handle_pipe2(t_full_cmd **cmd, t_data *data);
int		ft_logical_and2(t_full_cmd **cmd, t_data *data, int status);
int		ft_logical_or2(t_full_cmd **cmd, t_data *data, int status);

/* pipe */
void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int		ft_parent(t_full_cmd *cmd, t_data *data, t_pipe pipex);
int		ft_fork(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int		ft_pipe(t_full_cmd **cmd, t_data *data, int count);

/* redirections */
void	ft_heredoc(char *delimiter);
void	ft_redirect(t_redir_type *redirections, char **targets);
void	ft_reset_redirect(t_redir_type *redirections, char **targets);

/* signals */
void	ft_handle_sigint(int signal);
void	ft_sig_init(void);

/* utils */
int		ft_tablen(char **tab);
int		ft_find_var(char *env, char *name);

#endif
