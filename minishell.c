/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/30 16:15:04 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_program;

char	*ft_pwd_name(t_data *data)
{
	int		i;
	int		len;
	char	*cwd;

	i = 0;
	cwd = ft_getenv("PWD", data->env);
	len = ft_strlen(cwd);
	while (cwd[len - i] != '/')
		i++;
	cwd = ft_strdup(cwd + (len - i));
	return (cwd);
}

char	*ft_create_prompt(t_data *data)
{
	int		i;
	int		len;
	char	*cwd;
	char		*prompt;

	i = 0;
	cwd = ft_getenv("PWD", data->env);
	len = ft_strlen(cwd);
	while (cwd[len - i] != '/')
		i++;
	cwd = ft_strdup(cwd + (len - i));
	prompt = ft_strjoinjoin("🫠 \033[1;36m:~", cwd, "  \033[0m");
	free(cwd);
	return (prompt);
}

t_data	ft_init(char **env)
{
	t_data	data;
	//t_ast	ast;

	data.env = ft_cpyenv(env);
	data.history = NULL;
	//ast.cmds = NULL;
	//ast.operators = NULL;
	//data.ast = &ast;
	ft_sig_init();

	// int	i;
	// i = 0;
	// while (data.env[i])
	// {
	// 	printf("%i: %s\n", i, data.env[i]);
	// 	i++;
	// }
	return (data);
}

int	ft_readline(t_data data)
{
	char		*line;
	char		*prompt;
	t_full_cmd	*cmd;

	prompt = ft_create_prompt(&data);
	line = readline(prompt);
	if (!line)
	{
		free(prompt);
		ft_free_data(&data);
		return (1);
	}
	add_history(line);
	data.history = history_list();
	cmd = parse(line, data.env);
	ft_check_operators2(cmd, &data);
	ft_free_cmd(cmd);
	free(prompt);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	int			status;

	(void)argv;
	if (argc == 1)
	{
		data = ft_init(env);
		while (!status)
			status = ft_readline(data);
	}
	else
		printf("Too many args\n");
	return (0);
}

// int	main(int argc, char **argv, char **env)
// {
// 	t_data		data;
// 	char		*line;
// 	char		*prompt;
// 	t_full_cmd	*cmd;

// 	(void)argv;
// 	if (argc == 1)
// 	{
// 		data = ft_init(env);
// 		while (!g_program)
// 		{
// 			prompt = ft_strjoinjoin("🫠 \033[1;36m:~", ft_pwd_name(&data),
// 					"  \033[0m");
// 			line = readline(prompt);
// 			if (!line)
// 			{
// 				free(prompt);
// 				// ft_free_data(&data);
// 				break ;
// 			}
// 			add_history(line);
// 			data.history = history_list();
// 			cmd = parse(line, data.env);
// 			ft_check_operators2(cmd, &data);
// 			free(prompt);
// 			// printf("%s\n", line);
// 		}
// 	}
// 	else
// 		printf("Too many args\n");
// 	return (0);
// }
