/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/01 14:38:33 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

static int	g_program;

typedef struct s_cmd
{
	char	*cmd;
	char	**options;
	char	**args;
	char	**env;
}			t_cmd;

/* builtins */
int			ft_echo(t_cmd *cmd);
void		ft_pwd(t_cmd *cmd);
void		ft_env(t_cmd *cmd);

/* builtins2 */
int			ft_cd(t_cmd *cmd);
int			ft_export(t_cmd *cmd);
int			ft_unset(t_cmd *cmd);

/* utils */
char		*ft_free_matrix(char **matrix);
char		*ft_free_cmd(t_cmd *cmd);
int			ft_find_var(char *env, char *name);

/* env */
char		**ft_deallocenv(char **env, int size, char *name);
char		**ft_reallocenv(char **env, int size);
char		**ft_cpyenv(char **env);
char		*ft_getenv(char *name, char **env);
char		*ft_setenv(char *name, char *value, char **env);

#endif
