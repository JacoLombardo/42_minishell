/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 13:48:35 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/09 16:29:40 by jalombar         ###   ########.fr       */
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
int		ft_exit(t_full_cmd *cmd, t_data *data);
int		ft_handle_export(char *arg, t_data *data);
int		ft_export(t_full_cmd *cmd, t_data *data);
int		ft_pwd(t_full_cmd *cmd, t_data *data);
int		ft_handle_unset(char *arg, t_data *data);
int		ft_unset(t_full_cmd *cmd, t_data *data);

/* env */
char	*ft_getenv(char *name, char **env);
char	*ft_setenv(char *name, char *value, char **env);
int		ft_change_env(char *var, t_data *data);
char	**ft_cpyenv(char **env);
char	**ft_reallocenv(char **env, int size);
int		ft_set_pwd(char *pwd, t_data *data, int swap);

/* error */
void	ft_put_error(char *s1, char *s2, char *s3, int quotes);
int		ft_builtins_error(char *cmd, char *arg, int type);
int		ft_pipe_error(t_full_cmd *cmd, t_data *data, t_pipe pipex, char *error);
int		ft_file_error(char *path, int error);
void	ft_error(char *error, int status);

/* error2 */
int		ft_malloc_error(char *s1, char **tab, int index);
char	*ft_malloc_error1(char *s1, char **tab, int index);
char	**ft_malloc_error2(char *s1, char **tab, int index);

/* exec */
int		ft_builtins(t_full_cmd *cmd, t_data *data, int status);
int		ft_exec_redir(t_full_cmd *cmd, t_data *data, int status);
int		ft_exec(t_full_cmd *cmd, t_data *data);
int		ft_if_pipes(t_full_cmd *cmd, t_data *data);

/* free */
int		ft_clean_house(t_full_cmd *cmd, t_data *data, int status, int child);
void	ft_free_both_tab(char **tab1, char **tab2);
void	ft_free_tab(char **tab);
void	ft_cleanup_list(t_full_cmd *cmd);
void	ft_free_data_temps(t_data *data, int child);

/* heredoc */
void	ft_heredoc(char *delimiter, t_data *data, int flag);

/* pipe */
void	ft_child(t_full_cmd *cmd, t_data *data, t_pipe pipex);
int		ft_parent(t_pipe pipex);
int		ft_fork(t_full_cmd *cmd, t_data *data, t_pipe pipex);
int		ft_pipe(t_full_cmd *cmd, t_data *data);

/* redirections */
int		ft_redirect(t_redir_type *redirections, char **targets, t_data *data);
void	ft_reset_redirect(int saved_stdin, int saved_stdout);

/* signals */
void	ft_handle_sigint(int signal);
void	ft_handle_sigint_heredoc(int signal);
void	ft_handle_sigint_bin(int signal);
void	ft_handle_sigquit(int signal);
void	ft_sig_init(void);

/* subshell */
int		ft_subshell(t_full_cmd *cmd, t_data *data, int status);

/* utils */
int		ft_listlen(t_full_cmd *cmd);
int		ft_tablen(char **tab);
int		ft_filelen(char *path);
char	*trim_trailing_slash(char *path);

/* var */
int		ft_check_var_valid(char *var);
char	*ft_dup_var_name(char *var);
char	*ft_dup_var_value(char *var);
char	*ft_get_var_value(char *var);
int		ft_find_var(char *env, char *name);

#endif
