/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 16:11:14 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtins_main(int argc, char **argv, char **env)
{
	t_cmd	cmd;
	int		i;
	int		opt;

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
		ft_echo(&cmd);
	}
	else if (!ft_strcmp(argv[1], "pwd"))
		ft_pwd(&cmd);
	else if (!ft_strcmp(argv[1], "env"))
		ft_env(&cmd);
	else if (!ft_strcmp(argv[1], "cd"))
	{
		cmd.args = (char **)malloc(2 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = NULL;
		ft_cd(&cmd);
	}
	else if (!ft_strcmp(argv[1], "export"))
	{
		cmd.args = (char **)malloc(3 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = ft_strdup(argv[3]);
		cmd.args[2] = NULL;
		ft_export(&cmd);
	}
	else if (!ft_strcmp(argv[1], "unset"))
	{
		cmd.args = (char **)malloc(2 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = NULL;
		ft_unset(&cmd);
	}
	return (1);
}

int	main(int argc, char **argv, char **env)
{
	ft_builtins_main(argc, argv, env);
	return (0);
}
