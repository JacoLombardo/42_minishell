/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 11:48:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"
# include <stdio.h>

typedef struct s_cmd
{
	char	*cmd;
	char	**options;
	char	**args;
	char	**env;
}			t_cmd;

/* buildins */
int			ft_echo(t_cmd *cmd, int fd);
int			ft_pwd(t_cmd *cmd, int fd);
int			ft_env(t_cmd *cmd, int fd);
int			ft_cd(t_cmd *cmd, int fd);

/* utils */
char		**ft_cpyenv(char **env);
char		*ft_getenv(char *name, char **env);
char		*ft_setenv(char *name, char *value, char **env);

#endif