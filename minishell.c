/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/01 15:37:25 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	ft_builtins_main(int argc, char **argv, char **env)
{
	t_cmd	cmd;
	int		i;
	int		opt;

	if (argc == 0)
		return (0);
	i = 0;
	opt = 0;
	if (!ft_strcmp(argv[1], "echo"))
	{
		if (argv[2][0] == '-')
		{
			cmd.options = (char **)malloc(2 * sizeof(char *));
			cmd.options[0] = ft_strdup("-n");
			cmd.options[1] = NULL;
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
} */

char	*ft_pwd_name(t_cmd *cmd)
{
	int		i;
	int		len;
	char	*cwd;

	i = 0;
	cwd = ft_getenv("PWD", cmd->env);
	len = ft_strlen(cwd);
	while (cwd[len - i] != '/')
		i++;
	cwd = ft_strdup(cwd + (len - i));
	return (cwd);
}

int	main(int argc, char **argv, char **env)
{
	char	*line;
	char	*prompt;
	t_cmd	cmd;

	(void)argv;
	cmd.env = ft_cpyenv(env);
	if (argc == 1)
	{
		g_program = 1;
		while (g_program)
		{
			prompt = ft_strjoinjoin("🫠 :~", ft_pwd_name(&cmd), "$ ");
			line = readline(prompt);
			free(prompt);
			printf("%s\n", line);
		}
	}
	else
		perror("Too many args\n");
	return (0);
}
