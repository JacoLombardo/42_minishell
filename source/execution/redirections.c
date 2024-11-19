/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:56:25 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/15 15:18:32 by jalombar         ###   ########.fr       */
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

void	ft_in_redirect(t_redir_type redirection, char *target, t_dup2 *fds,
		t_data *data)
{
	char	*temp;

	temp = NULL;
	if (redirection == R_IN)
	{
		fds->to_fd = open(target, O_RDONLY, 0777);
		fds->from_fd = 0;
	}
	else if (redirection == R_HEREDOC)
	{
		temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
		fds->to_fd = open(temp, O_RDONLY, 0777);
		free(temp);
		fds->from_fd = 0;
	}
}

void	ft_out_redirect(t_redir_type redirection, char *target, t_dup2 *fds)
{
	if (redirection == R_OUT)
	{
		fds->to_fd = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0777);
		fds->from_fd = 1;
	}
	else if (redirection == R_APPEND)
	{
		fds->to_fd = open(target, O_WRONLY | O_CREAT | O_APPEND, 0777);
		fds->from_fd = 1;
	}
}

int	ft_redirect(t_redir_type *redirections, char **targets, t_data *data)
{
	int		i;
	t_dup2	fds;

	i = 0;
	fds.from_fd = 0;
	fds.to_fd = -1;
	while (targets[i])
	{
		if (redirections[i] == R_IN || redirections[i] == R_HEREDOC)
			ft_in_redirect(redirections[i], targets[i], &fds, data);
		else if (redirections[i] == R_OUT || redirections[i] == R_APPEND)
			ft_out_redirect(redirections[i], targets[i], &fds);
		if (fds.to_fd < 0)
		{
			perror(targets[i]);
			return (1);
		}
		dup2(fds.to_fd, fds.from_fd);
		close(fds.to_fd);
		i++;
	}
	return (0);
}

void	ft_reset_redirect(int saved_stdin, int saved_stdout)
{
	dup2(saved_stdin, STDIN_FILENO);
	dup2(saved_stdout, STDOUT_FILENO);
	close(saved_stdin);
	close(saved_stdout);
}
