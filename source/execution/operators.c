/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/11 13:51:46 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_skip_pipe(t_cmd **cmd, t_data *data, char ***operators)
{
	(void)data;
	//printf("inside skip: cmd-%s, op-%s\n", (*cmd)->cmd, **operators);
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

int	ft_handle_pipe(t_cmd **cmd, t_data *data, char ***operators)
{
	int	count;
	int	status;

	count = 1;
	//printf("inside handle: cmd-%s, op-%s\n", (*cmd)->cmd, **operators);
	if (**operators && !ft_strcmp(**operators, "|"))
	{
		while (**operators && !ft_strcmp(**operators, "|"))
		{
			(*operators)++;
			count++;
		}
		status = ft_pipe(cmd, data, count);
	}
	else
	{
		status = ft_exec(*cmd, data);
		*cmd = (*cmd)->next;
	}
	return (status);
}

int	ft_logical_and(t_cmd **cmd, t_data *data, char ***operators, int status)
{
	(*operators)++;
	if (!status)
		status = ft_handle_pipe(cmd, data, operators);
	else
		ft_skip_pipe(cmd, data, operators);
	return (status);
}

int	ft_logical_or(t_cmd **cmd, t_data *data, char ***operators, int status)
{
	(*operators)++;
	if (status > 0 || status < 0)
		status = ft_handle_pipe(cmd, data, operators);
	else
		ft_skip_pipe(cmd, data, operators);
	return (status);
}
