/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:21:18 by csilva-r          #+#    #+#             */
/*   Updated: 2024/12/08 18:17:41 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

static void	ft_write_heredoc(int fd, char *line, int flag, t_data *data)
{
	char	*temp;

	if (flag)
	{
		temp = expand_vars(line, data);
		ft_putstr_fd(temp, fd);
		free(temp);
	}
	else
		ft_putstr_fd(line, fd);
	ft_putchar_fd('\n', fd);
}

void	ft_heredoc_child(int fd, char *delimiter, t_data *data, int flag)
{
	char	*line;
	char	*trimmed;

	signal(SIGQUIT, ft_handle_sigquit);
	signal(SIGINT, ft_handle_sigint2);
	trimmed = trim_quote(delimiter);
	free(delimiter);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line || !ft_strcmp(line, trimmed))
		{
			free(line);
			break ;
		}
		ft_write_heredoc(fd, line, flag, data);
		free(line);
	}
	free(trimmed);
	ft_free_data_temps(data, 0);
	exit(0);
}

void	ft_heredoc(char *delimiter, t_data *data, int flag)
{
	int		fd;
	pid_t	pid;
	int		status;
	char	*temp;

	if (!data || !data->env)
		return ;
	temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
	fd = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	free(temp);
	if (fd < 0)
		ft_error("open", 1);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
		ft_heredoc_child(fd, delimiter, data, flag);
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			data->error = WEXITSTATUS(status);
	}
}

