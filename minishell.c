/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 13:26:23 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/17 15:28:50 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_create_prompt(t_data *data)
{
	int		i;
	int		len;
	char	*cwd;
	char	*prompt;

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
	int	fd;
	t_data	data;

	fd = 3;
	while (fd < 124)
	{
		close(fd);
		fd++;
	}
	data.env = ft_cpyenv(env);
	if (ft_getenv("SHELL_ID", data.env))
	{
		data.shell_id = ft_atoi(ft_getenv("SHELL_ID", data.env));
		ft_handle_unset("SHELL_ID", &data);
	}
	else
		data.shell_id = 0;
	data.history = NULL;
	data.last_exit = 0;
	ft_sig_init();
	return (data);
}

void	ft_handle_line(char *line, t_data *data)
{
	t_full_cmd	*cmd;

	add_history(line);
	data->history = history_list();
	cmd = parse(line, data);
	if (!cmd)
		return ;
	//print_jacopo(cmd, 0);
	ft_if_pipes(cmd, data);
	ft_free_cmd(cmd);
}

int	ft_readline(t_data *data)
{
	char	*line;
	char	*prompt;

	prompt = ft_create_prompt(data);
	line = readline(prompt);
	if (!line)
	{
		free(prompt);
		ft_free_data_temps(data);
		return (1);
	}
	free(prompt);
	if (ft_strlen(line))
		ft_handle_line(line, data);
	else
		free(line);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;
	int		status;

	(void)argv;
	status = 0;
	if (argc == 1)
	{
		data = ft_init(env);
		while (!status)
			status = ft_readline(&data);
	}
	else
	{
		ft_putstr_fd("Minishell: Too many arguments\n", 2);
		return (1);
	}
	return (0);
}
