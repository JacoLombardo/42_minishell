/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:21:18 by csilva-r          #+#    #+#             */
/*   Updated: 2024/12/10 11:09:52 by jalombar         ###   ########.fr       */
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

void	ft_handle_heredoc(char *delimiter, int fd, int flag, t_data *data)
{
	char	*line;
	char	*trimmed;

	trimmed = trim_quote(delimiter);
	while (!g_flag)
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
	close(fd);
	free(trimmed);
}

void	ft_heredoc(char *delimiter, t_data *data, int flag)
{
	int		fd;
	char	*temp;

	if (!data || !data->env)
		return ;
	temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
	fd = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	free(temp);
	if (fd < 0)
		ft_error("open", 1);
	signal(SIGINT, ft_handle_sigint_heredoc);
	ft_handle_heredoc(delimiter, fd, flag, data);
	signal(SIGINT, ft_handle_sigint);
}
