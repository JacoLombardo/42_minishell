/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/29 16:21:41 by jalombar         ###   ########.fr       */
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

t_ast	*ft_set(void)
{
	t_ast		*ast;
	t_full_cmd	*cmd1;
	t_full_cmd	*cmd2;
	t_full_cmd	*cmd3;
	t_full_cmd	*cmd4;
	t_full_cmd	*cmd5;
	t_full_cmd	*cmd6;
	t_full_cmd	*cmd7;
	t_full_cmd	*cmd8;

	ast = (t_ast *)malloc(sizeof(t_full_cmd));
	ast->operators = NULL;
	ast->cmds = NULL;
	ast->operators = (char **)malloc(8 * sizeof(char *));
	ast->operators[0] = ft_strdup("|");
	ast->operators[1] = ft_strdup("|");
	ast->operators[2] = ft_strdup("|");
	ast->operators[3] = ft_strdup("&&");
	ast->operators[4] = ft_strdup("|");
	ast->operators[5] = ft_strdup("|");
	ast->operators[6] = ft_strdup("&&");
	ast->operators[7] = NULL;
	cmd1 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd1->args = (char **)malloc(4 * sizeof(char *));
	cmd1->args[0] = ft_strdup("echo");
	cmd1->args[1] = ft_strdup("molot");
	cmd1->args[2] = ft_strdup("male");
	cmd1->args[3] = NULL;
	cmd1->cmd = cmd1->args[0];
	cmd1->redirections = NULL;
	cmd1->targets = NULL;
	/* cmd1 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd1->args = (char **)malloc(2 * sizeof(char *));
	cmd1->args[0] = ft_strdup("cat");
	cmd1->args[1] = NULL;
	cmd1->cmd = cmd1->args[0];
	cmd1->redirection = ft_strdup("<<");
	cmd1->target = ft_strdup("ciao");
	cmd1->next = NULL; */
	cmd2 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd2->args = (char **)malloc(2 * sizeof(char *));
	cmd2->args[0] = ft_strdup("cat");
	cmd2->args[1] = NULL;
	cmd2->cmd = cmd2->args[0];
	cmd2->redirections = NULL;
	cmd2->targets = NULL;
	cmd3 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd3->args = (char **)malloc(3 * sizeof(char *));
	cmd3->args[0] = ft_strdup("wc");
	cmd3->args[1] = ft_strdup("-l");
	cmd3->args[2] = NULL;
	cmd3->cmd = cmd3->args[0];
	cmd3->redirections = NULL;
	cmd3->targets = NULL;
	cmd4 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd4->args = (char **)malloc(2 * sizeof(char *));
	cmd4->args[0] = ft_strdup("cat");
	cmd4->args[1] = NULL;
	cmd4->cmd = cmd4->args[0];
	cmd4->redirections = NULL;
	cmd4->targets = NULL;
	cmd5 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd5->args = (char **)malloc(2 * sizeof(char *));
	cmd5->args[0] = ft_strdup("cat");
	cmd5->args[1] = NULL;
	cmd5->cmd = cmd5->args[0];
	cmd5->redirections = NULL;
	cmd5->targets = NULL;
	cmd6 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd6->args = (char **)malloc(3 * sizeof(char *));
	cmd6->args[0] = ft_strdup("wc");
	cmd6->args[1] = ft_strdup("-l");
	cmd6->args[2] = NULL;
	cmd6->cmd = cmd6->args[0];
	cmd6->redirections = NULL;
	cmd6->targets = NULL;
	cmd7 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd7->args = (char **)malloc(2 * sizeof(char *));
	cmd7->args[0] = ft_strdup("cat");
	cmd7->args[1] = NULL;
	cmd7->cmd = cmd7->args[0];
	cmd7->redirections = NULL;
	cmd7->targets = NULL;
	/* cmd7->redirections = ft_strdup(">");
	cmd7->targets = ft_strdup("text2.txt"); */
	cmd8 = (t_full_cmd *)malloc(1 * sizeof(t_full_cmd));
	cmd8->args = (char **)malloc(4 * sizeof(char *));
	cmd8->args[0] = ft_strdup("cat");
	cmd8->args[1] = ft_strdup("text.txt");
	cmd8->args[2] = ft_strdup("text3.txt");
	cmd8->args[3] = NULL;
	cmd8->cmd = cmd8->args[0];
	cmd8->redirections = NULL;
	cmd8->targets = NULL;
	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = cmd4;
	cmd4->next = cmd5;
	cmd5->next = cmd6;
	cmd6->next = cmd7;
	cmd7->next = cmd8;
	cmd8->next = NULL;
	ast->cmds = (t_full_cmd **)malloc(sizeof(t_full_cmd *));
	*ast->cmds = cmd1;
	return (ast);
}

void	ft_check(t_full_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd)
	{
		print_jacopo(cmd, i);
		cmd = cmd->next;
		i++;
	}
	printf("\n");
}

t_data	ft_init(char **env)
{
	t_data	data;
	t_ast	ast;

	data.env = ft_cpyenv(env);
	data.history = NULL;
	ast.cmds = NULL;
	ast.operators = NULL;
	data.ast = &ast;
	ft_sig_init();
	return (data);
}

int	main(int argc, char **argv, char **env)
{
	t_data		data;
	char		*line;
	char		*prompt;
	t_full_cmd	*cmd;

	(void)argv;
	if (argc == 1)
	{
		data = ft_init(env);
		// data.ast = ft_set();
		// ft_check(&ast);
		// ft_check_operators(&ast, &data);
		while (!g_program)
		{
			prompt = ft_strjoinjoin("🫠 \033[1;36m:~", ft_pwd_name(&data),
					"  \033[0m");
			line = readline(prompt);
			if (!line)
			{
				free(prompt);
				// ft_free_data(&data);
				break ;
			}
			add_history(line);
			data.history = history_list();
			cmd = parse(line, data.env);
			ft_check_operators2(cmd, &data);
			free(prompt);
			// printf("%s\n", line);
		}
	}
	else
		printf("Too many args\n");
	return (0);
}
