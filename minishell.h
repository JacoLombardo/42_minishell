/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:48 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/27 11:32:18 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries/libft/libft.h"

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

#endif