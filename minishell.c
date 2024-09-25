/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/25 16:46:18 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//int	main(int argc, char **argv, char **env)
int	main(void)
{
	t_cmd	cmd;

	//cmd.options = (char **)malloc(1 * sizeof(char *));
	cmd.options = NULL;
	//cmd.options[0] = ft_strdup("-n");
	cmd.args = (char **)malloc(3 + 1 * sizeof(char *));
	cmd.args[0] = ft_strdup("ciao ");
	cmd.args[1] = ft_strdup("come ");
	cmd.args[2] = ft_strdup("stai");
	cmd.args[3] = NULL;
	ft_echo(&cmd, 1);
	ft_pwd(&cmd, 1);
	return (0);
}
