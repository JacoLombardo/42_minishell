/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/16 14:16:00 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_skip_pipe2(t_full_cmd **cmd, t_data *data)
{
	(void)data;
	if ((*cmd)->operator&& !ft_strcmp((*cmd)->operator, "|"))
	{
		while (*cmd && !ft_strcmp((*cmd)->operator, "|"))
			*cmd = (*cmd)->next;
	}
	else
		*cmd = (*cmd)->next;
}

int	ft_handle_pipe2(t_full_cmd **cmd, t_data *data)
{
	int		cmd_count;
	int		status;
	t_full_cmd	*temp;

	cmd_count = 1;
	temp = *cmd;
	if (temp->operator && !ft_strcmp(temp->operator, "|"))
	{
		while (temp->operator && !ft_strcmp(temp->operator, "|"))
		{
			temp = temp->next;
			cmd_count++;
		}
		status = ft_pipe2(cmd, data, cmd_count);
	}
	else
		status = ft_exec(*cmd, data);
	return (status);
}

int	ft_logical_and2(t_full_cmd **cmd, t_data *data, int status)
{
	*cmd = (*cmd)->next;
	if (!status)
		status = ft_handle_pipe2(cmd, data);
	else
		ft_skip_pipe2(cmd, data);
	return (status);
}

int	ft_logical_or2(t_full_cmd **cmd, t_data *data, int status)
{
	*cmd = (*cmd)->next;
	if (status > 0 || status < 0)
		status = ft_handle_pipe2(cmd, data);
	else
		ft_skip_pipe2(cmd, data);
	return (status);
}

void	ft_skip_pipe(t_full_cmd **cmd, t_data *data, char ***operators)
{
	(void)data;
	if (**operators && !ft_strcmp(**operators, "|"))
	{
		while (**operators && !ft_strcmp(**operators, "|"))
		{
			(*operators)++;
			*cmd = (*cmd)->next;
		}
		*cmd = (*cmd)->next;
	}
	else
		*cmd = (*cmd)->next;
}

int	ft_handle_pipe(t_full_cmd **cmd, t_data *data, char ***operators)
{
	int	cmd_count;
	int	status;

	cmd_count = 1;
	if (**operators && !ft_strcmp(**operators, "|"))
	{
		while (**operators && !ft_strcmp(**operators, "|"))
		{
			(*operators)++;
			cmd_count++;
		}
		status = ft_pipe(cmd, data, cmd_count);
	}
	else
	{
		status = ft_exec(*cmd, data);
		*cmd = (*cmd)->next;
	}
	return (status);
}

int	ft_logical_and(t_full_cmd **cmd, t_data *data, char ***operators, int status)
{
	(*operators)++;
	if (!status)
		status = ft_handle_pipe(cmd, data, operators);
	else
		ft_skip_pipe(cmd, data, operators);
	return (status);
}

int	ft_logical_or(t_full_cmd **cmd, t_data *data, char ***operators, int status)
{
	(*operators)++;
	if (status > 0 || status < 0)
		status = ft_handle_pipe(cmd, data, operators);
	else
		ft_skip_pipe(cmd, data, operators);
	return (status);
}
