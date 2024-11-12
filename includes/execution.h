/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:48:35 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/12 15:20:02 by jalombar         ###   ########.fr       */
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

t_data	ft_init(char **env);

/* bin */
char	*ft_get_path(char *cmd, char **env);
int		ft_bin(t_full_cmd *cmd, t_data *data, int status);

/* builtins */
int		ft_cd(t_full_cmd *cmd, t_data *data);
int		ft_echo(t_full_cmd *cmd, t_data *data);
int		ft_env(t_full_cmd *cmd, t_data *data);
void	ft_exit(t_full_cmd *cmd, t_data *data);
int		ft_export(t_full_cmd *cmd, t_data *data);
int		ft_pwd(t_full_cmd *cmd, t_data *data);
int		ft_unset(t_full_cmd *cmd, t_data *data);

/* env */
char	*ft_getenv(char *name, char **env);
char	*ft_setenv(char *name, char *value, char **env);
int		ft_change_env(char *var, t_data *data);
char	**ft_cpyenv(char **env);

/* error */
int		ft_file_error(char *path, int error);
void	ft_error(char *error, int status);

/* exec */
int		ft_builtins(t_full_cmd *cmd, t_data *data, int status);
int		ft_exec(t_full_cmd *cmd, t_data *data);
int		ft_if_pipes(t_full_cmd *cmd, t_data *data);

/* free */
void	ft_free_both_tab(char **tab1, char **tab2);
void	ft_free_tab(char **tab);
void	ft_free_cmd(t_full_cmd *cmd);
void	ft_free_data_temps(t_data *data);

/* pipe */
void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int		ft_parent(t_full_cmd *cmd, t_data *data, t_pipe pipex);
int		ft_fork(t_full_cmd *cmd, t_data *data, t_pipe pipex, int flag);
int		ft_pipe(t_full_cmd **cmd, t_data *data, int count);
int		ft_handle_pipe(t_full_cmd **cmd, t_data *data);

/* redirections */
void	ft_heredoc(char *delimiter, t_data *data, int flag);
int		ft_redirect(t_redir_type *redirections, char **targets);
void	ft_reset_redirect(int saved_stdin, int saved_stdout);

/* signals */
void	ft_handle_sigint(int signal);
void	ft_sig_init(void);

/* utils */
int		ft_tablen(char **tab);

/* var */
int		ft_check_var_valid(char *var);
char	*ft_get_var_name(char *var);
int		ft_find_var(char *env, char *name);

#endif
