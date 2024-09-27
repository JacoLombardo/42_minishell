/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/27 11:37:32 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
//int	main(void)
{
	t_cmd	cmd;
	int		i;

	if (argc == 0)
		return (0);
	i = 0;
	//cmd.options = (char **)malloc(1 * sizeof(char *));
	cmd.options = NULL;
	//cmd.options[0] = ft_strdup("-n");
	cmd.args = (char **)malloc(3 + 1 * sizeof(char *));
	while (argv[i + 1])
	{
		cmd.args[i] = ft_strdup(argv[i + 1]);
		i++;
	}
	// cmd.args[0] = ft_strdup(argv);
	// cmd.args[1] = ft_strdup("come ");
	// cmd.args[2] = ft_strdup("stai");
	cmd.args[i] = NULL;
	cmd.env = env;
	ft_echo(&cmd, 1);
	ft_pwd(&cmd, 1);
	ft_env(&cmd, 1);
	return (0);
}
