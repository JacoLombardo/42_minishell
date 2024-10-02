/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/02 14:45:45 by jalombar         ###   ########.fr       */
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
# include <signal.h>
# include <asm-generic/siginfo.h>

static int			g_program;

typedef struct s_status
{
	char			*cmd;
	int				exit_status;
	struct s_status	*next;
}					t_status;

typedef struct s_data
{
	char			**env;
	HIST_ENTRY		**history;
	struct s_status	*ex_stat;
}					t_data;

typedef struct s_cmd
{
	char			*cmd;
	char			**options;
	char			**args;
}					t_cmd;

/* builtins */
int					ft_echo(t_cmd *cmd, t_data *data);
void				ft_pwd(t_cmd *cmd, t_data *data);
void				ft_env(t_cmd *cmd, t_data *data);

/* builtins2 */
int					ft_cd(t_cmd *cmd, t_data *data);
int					ft_export(t_cmd *cmd, t_data *data);
int					ft_unset(t_cmd *cmd, t_data *data);

/* env */
char				**ft_deallocenv(char **env, int size, char *name);
char				**ft_reallocenv(char **env, int size);
char				**ft_cpyenv(char **env);
char				*ft_getenv(char *name, char **env);
char				*ft_setenv(char *name, char *value, char **env);

/* exec */
int					ft_open_file(char *file, int in_or_out);
char				*ft_get_path(char *cmd, char **env);
void				ft_exec(char *cmd, t_data *data);

/* pipex */
void				ft_child(t_cmd *cmd, t_data *data, int *p_fd);
void				ft_parent(t_cmd *cmd, t_data *data, int *p_fd);
void				ft_pipex(t_cmd *cmd, t_data *data);

/* utils */
char				*ft_free_tab(char **tab);
char				*ft_free_cmd(t_cmd *cmd);
int					ft_find_var(char *env, char *name);

#endif