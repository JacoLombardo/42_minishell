/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/11 10:45:50 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

// void	sig_handler(int signum, siginfo_t *info, void *context)
// {
// 	(void)context;
// 	(void)info;
// 	if (signum == SIGUSR1)
// 		g_program = 0;
// 	else if (signum == SIGUSR2)
// 		g_program = 2;
// }

t_ast	ft_set()
{
	t_ast ast;
	t_cmd *cmd1;
	t_cmd *cmd2;
	t_cmd *cmd3;
	t_cmd *cmd4;
	t_cmd *cmd5;
	t_cmd *cmd6;
	t_cmd *cmd7;
	t_cmd *cmd8;

	//ast.operators = NULL;
	ast.cmds = NULL;
	ast.operators = (char **)malloc(8 * sizeof(char *));
	ast.operators[0] = ft_strdup("|");
	ast.operators[1] = ft_strdup("|");
	ast.operators[2] = ft_strdup("|");
	ast.operators[3] = ft_strdup("&&");
	ast.operators[4] = ft_strdup("|");
	ast.operators[5] = ft_strdup("|");
	ast.operators[6] = ft_strdup("&&");
	ast.operators[7] = NULL;

	cmd1 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd1->args = (char **)malloc(4 * sizeof(char *));
	cmd1->args[0] = ft_strdup("echo");
	cmd1->args[1] = ft_strdup("ciao");
	cmd1->args[2] = ft_strdup("come");
	cmd1->args[3] = NULL;
	cmd1->cmd = cmd1->args[0];
	cmd1->redirection = NULL;
	cmd1->target = NULL;

	cmd2 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd2->args = (char **)malloc(2 * sizeof(char *));
	cmd2->args[0] = ft_strdup("cat");
	cmd2->args[1] = NULL;
	cmd2->cmd = cmd2->args[0];
	cmd2->redirection = NULL;
	cmd2->target = NULL;

	/* cmd3 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd3->args = (char **)malloc(2 * sizeof(char *));
	cmd3->args[0] = ft_strdup("cat");
	cmd3->args[1] = NULL;
	cmd3->cmd = cmd2->args[0];
	cmd3->redirection = NULL;
	cmd3->target = NULL; */

	cmd3 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd3->args = (char **)malloc(3 * sizeof(char *));
	cmd3->args[0] = ft_strdup("wc");
	cmd3->args[1] = ft_strdup("-l");
	cmd3->args[2] = NULL;
	cmd3->cmd = cmd3->args[0];
	cmd3->redirection = NULL;
	cmd3->target = NULL;

	cmd4 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd4->args = (char **)malloc(2 * sizeof(char *));
	cmd4->args[0] = ft_strdup("cat");
	cmd4->args[1] = NULL;
	cmd4->cmd = cmd4->args[0];
	cmd4->redirection = NULL;
	cmd4->target = NULL;

	cmd5 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd5->args = (char **)malloc(2 * sizeof(char *));
	cmd5->args[0] = ft_strdup("cat");
	//cmd5->args[1] = ft_strdup("dajeeeeee");
	cmd5->args[1] = NULL;
	cmd5->cmd = cmd5->args[0];
	cmd5->redirection = ft_strdup("<");
	cmd5->target = ft_strdup("text.txt");

	cmd6 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd6->args = (char **)malloc(3 * sizeof(char *));
	cmd6->args[0] = ft_strdup("wc");
	cmd6->args[1] = ft_strdup("-l");
	cmd6->args[2] = NULL;
	cmd6->cmd = cmd6->args[0];
	cmd6->redirection = NULL;
	cmd6->target = NULL;

	cmd7 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd7->args = (char **)malloc(2 * sizeof(char *));
	cmd7->args[0] = ft_strdup("cat");
	cmd7->args[1] = NULL;
	cmd7->cmd = cmd7->args[0];
	cmd7->redirection = ft_strdup(">");
	cmd7->target = ft_strdup("text2.txt");

	cmd8 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd8->args = (char **)malloc(3 * sizeof(char *));
	cmd8->args[0] = ft_strdup("echo");
	cmd8->args[1] = ft_strdup("fine :)");
	cmd8->args[2] = NULL;
	cmd8->cmd = cmd8->args[0];
	cmd8->redirection = NULL;
	cmd8->target = NULL;

	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = cmd4;
	cmd4->next = cmd5;
	cmd5->next = cmd6;
	cmd6->next = cmd7;
	cmd7->next = cmd8;
	cmd8->next = NULL;

	ast.cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*ast.cmds = cmd1;
	return (ast);
}

void	ft_check(t_ast *ast)
{
	t_cmd	*cmd;
	char	**operators;

	cmd = *ast->cmds;
	operators = ast->operators;
	while (*operators)
	{
		printf("%s\n", *operators);
		operators++;
	}
	while (cmd)
	{
		printf("%s\n", cmd->cmd);
		cmd = cmd->next;
	}
}

int	main(int argc, char **argv, char **env)
{
	//struct sigaction	sa;
	/* char				*line;
	char				*prompt; */
	t_data				data;
	HIST_ENTRY			**history;
	t_ast				ast;

	(void)argv;
	/* sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL); */
	data.env = ft_cpyenv(env);
	history = NULL;
	data.history = history;
	ast = ft_set();
	//ft_check(&ast);
	//pipex(*ast.cmds, &data);
	ft_check_operators(&ast, &data);
	if (argc == 1)
	{
		/*
		//g_program = 1;
		//while (g_program)
		while (1)
		{
			prompt = ft_strjoinjoin("🫠 :~", ft_pwd_name(&data), "$ ");
			line = readline(prompt);
			add_history(line);
			history = history_list();
			//ft_exec(line, &data);
			free(prompt);
			for (int i = 0; history[i] != NULL; i++)
				printf("%d: %s\n", i + history_base, history[i]->line);
		}
		*/
	}
	else
		printf("Too many args\n");
	return (0);
}
