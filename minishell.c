/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/08 18:26:15 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	ft_builtins_main(int argc, char **argv, t_data *data)
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
		ft_echo(&cmd, data);
	}
	else if (!ft_strcmp(argv[1], "pwd"))
		ft_pwd(&cmd, data);
	else if (!ft_strcmp(argv[1], "env"))
		ft_env(&cmd, data);
	else if (!ft_strcmp(argv[1], "cd"))
	{
		cmd.args = (char **)malloc(2 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = NULL;
		ft_cd(&cmd, data);
	}
	else if (!ft_strcmp(argv[1], "export"))
	{
		cmd.args = (char **)malloc(3 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = ft_strdup(argv[3]);
		cmd.args[2] = NULL;
		ft_export(&cmd, data);
	}
	else if (!ft_strcmp(argv[1], "unset"))
	{
		cmd.args = (char **)malloc(2 * sizeof(char *));
		cmd.args[0] = ft_strdup(argv[2]);
		cmd.args[1] = NULL;
		ft_unset(&cmd, data);
	}
	return (1);
} */

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

	//ast.operators = NULL;
	ast.cmds = NULL;
	ast.operators = (char **)malloc(4 * sizeof(char *));
	ast.operators[0] = ft_strdup("|");
	ast.operators[1] = ft_strdup("|");
	ast.operators[2] = NULL;
	ast.operators[2] = ft_strdup("&&");
	ast.operators[3] = NULL;

	cmd1 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd1->args = (char **)malloc(4 * sizeof(char *));
	cmd1->args[0] = ft_strdup("echo");
	cmd1->args[1] = ft_strdup("ciao");
	cmd1->args[2] = ft_strdup("come");
	cmd1->args[3] = NULL;
	cmd1->cmd = cmd1->args[0];
	cmd1->redirection = NULL;
	cmd1->target = NULL;
	//cmd1->next = NULL;

	cmd2 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd2->args = (char **)malloc(2 * sizeof(char *));
	cmd2->args[0] = ft_strdup("cat");
	cmd2->args[1] = NULL;
	cmd2->cmd = cmd2->args[0];
	cmd2->redirection = NULL;
	cmd2->target = NULL;

	cmd3 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd3->args = (char **)malloc(3 * sizeof(char *));
	cmd3->args[0] = ft_strdup("wc");
	cmd3->args[1] = ft_strdup("-l");
	cmd3->args[2] = NULL;
	cmd3->cmd = cmd3->args[0];
	cmd3->redirection = NULL;
	cmd3->target = NULL;

	cmd4 = (t_cmd *)malloc(1 * sizeof(t_cmd));
	cmd4->args = (char **)malloc(3 * sizeof(char *));
	cmd4->args[0] = ft_strdup("echo");
	cmd4->args[1] = ft_strdup("bene");
	cmd4->args[2] = NULL;
	cmd4->cmd = cmd4->args[0];
	cmd4->redirection = NULL;
	cmd4->target = NULL;

	cmd1->next = cmd2;
	cmd2->next = cmd3;
	cmd3->next = cmd4;
	cmd4->next = NULL;

	ast.cmds = (t_cmd **)malloc(sizeof(t_cmd *));
	*ast.cmds = cmd1;
	return (ast);
}

void	ft_check(t_ast *ast)
{
	t_cmd *cmd;
	char **operators;

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
	char				*line;
	char				*prompt;
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
