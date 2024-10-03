/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 17:59:53 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/02 14:10:11 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_open_file(char *file, int in_or_out)
{
	int	ret;

	if (in_or_out == 0)
		ret = open(file, O_RDONLY, 0777);
	if (in_or_out == 1)
		ret = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (ret == -1)
		exit(0);
	return (ret);
}

char	*ft_get_path(char *cmd, char **env)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = 0;
	allpath = ft_split(ft_getenv("PATH", env), ':');
	s_cmd = ft_split(cmd, ' ');
	while (allpath[i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		exec = ft_strjoin(path_part, s_cmd[0]);
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_tab(s_cmd);
			return (exec);
		}
		free(exec);
		i++;
	}
	ft_free_tab(allpath);
	ft_free_tab(s_cmd);
	return (cmd);
}

/* void	ft_exec(char *cmd, char **env)
{
	char	**s_cmd;
	char	*path;

	s_cmd = ft_split(cmd, ' ');
	path = ft_get_path(s_cmd[0], env);
	if (execve(path, s_cmd, env) == -1)
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		ft_putendl_fd(s_cmd[0], 2);
		ft_free_tab(s_cmd);
		exit(0);
	}
} */

void	ft_new_ex_stat(t_status **ex_stat, int status, char *cmd)
{
	t_status	*node;

	node = (t_status *)malloc(1 * sizeof(t_status));
	node->cmd = ft_strdup(cmd);
	node->exit_status = status;
	node->next = *ex_stat;
	*ex_stat = node;
}

void	ft_exec(char *cmd, t_data *data)
{
	char	**s_cmd;
	char	*path;
	pid_t	pid;
	int		status;

	s_cmd = ft_split(cmd, ' ');
	path = ft_get_path(s_cmd[0], data->env);
	pid = fork();
	if (pid == -1)
		exit(-1);
	if (!pid)
	{
		if (execve(path, s_cmd, data->env) == -1)
		{
			ft_putstr_fd("minishell: command not found: ", 2);
			ft_putendl_fd(s_cmd[0], 2);
			ft_free_tab(s_cmd);
			exit(1);
		}
	}
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			ft_new_ex_stat(&data->ex_stat, WEXITSTATUS(status), cmd);
	}
	ft_free_tab(s_cmd);
}