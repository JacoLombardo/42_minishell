/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 12:26:07 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_cmd		cmd;
	int			i;
	int			opt;

	if (argc == 0)
		return (0);
	i = 0;
	opt = 0;
	cmd.env = ft_cpyenv(env);
	if (!ft_strcmp(argv[1], "echo"))
	{
		if (argv[2][0] == '-')
		{
			cmd.options = (char **)malloc(1 * sizeof(char *));
			cmd.options[0] = ft_strdup("-n");
			opt++;
		}
		else
			cmd.options = NULL;
		cmd.args = (char **)malloc((argc - 2 - opt) + 1 * sizeof(char *));
		while (argv[i + opt + 2])
		{
			cmd.args[i] = ft_strdup(argv[i + opt + 2]);
			i++;
		}
		cmd.args[i] = NULL;
		ft_echo(&cmd, 1);
	}
	else if (!ft_strcmp(argv[1], "pwd"))
		ft_pwd(&cmd, 1);
	else if (!ft_strcmp(argv[1], "env"))
		ft_env(&cmd, 1);
	else if (!ft_strcmp(argv[1], "cd"))
	{
		cmd.args = (char **)malloc(2 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = NULL;
		ft_cd(&cmd, 1);
	}
	return (0);
}
