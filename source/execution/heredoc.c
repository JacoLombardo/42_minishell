/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 12:21:18 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/22 12:21:23 by csilva-r         ###   ########.fr       */
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

void	ft_heredoc(char *delimiter, t_data *data, int flag)
{
	int		fd;
	char	*line;
	char	*trimmed;
	char	*temp;

	if (!data || !data->env)
		return ;
	temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
	fd = open(temp, O_CREAT | O_WRONLY | O_TRUNC, 0777);
	free(temp);
	if (fd < 0)
		ft_error("open", 1);
	trimmed = trim_quote(delimiter);
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
}
