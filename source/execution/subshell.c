/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 15:48:08 by jalombar          #+#    #+#             */
/*   Updated: 2024/12/09 14:28:35 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_subshell_child(t_full_cmd *cmd, t_data *data)
{
	char	*var;

	signal(SIGINT, ft_handle_sigint);
	var = ft_charjoin("SHELL_ID=", (data->shell_id + 1) + '0');
	if (!var)
		ft_error("malloc", 1);
	ft_handle_export(var, data);
	free(var);
	if (execve(cmd->cmd, cmd->args, data->env) == -1)
	{
		perror("Minishell: Error launching new shell");
		ft_handle_unset("SHELL_ID", data);
		exit(1);
	}
}

int	ft_subshell(t_full_cmd *cmd, t_data *data, int status)
{
	pid_t	pid;

	if (data->shell_id >= 4)
	{
		ft_putstr_fd("Minishell: Subshells limit reached\n", 2);
		return (1);
	}
	signal(SIGINT, SIG_IGN);
	pid = fork();
	if (pid == 0)
		ft_subshell_child(cmd, data);
	else if (pid > 0)
	{
		waitpid(pid, &status, 0);
		signal(SIGINT, ft_handle_sigint);
		if (WIFEXITED(status))
		{
			ft_handle_unset("SHELL_ID", data);
			return (WEXITSTATUS(status));
		}
	}
	return (status);
}
