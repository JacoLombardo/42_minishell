/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operators.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 11:26:07 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/09 16:21:57 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_logical_and(t_cmd **cmd, t_data *data, char ***operators)
{
	int	count;
	int	status;

	count = 1;
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
		(*operators)++;
		*cmd = (*cmd)->next;
	}
	return (status);
}

void	ft_logical_or(t_cmd **cmd, t_data *data, char ***operators)
{
	int	count;

	(void)data;
	count = 0;
	if (**operators && !ft_strcmp(**operators, "|"))
	{
		while (**operators && !ft_strcmp(**operators, "|"))
		{
			(*operators)++;
			count++;
			*cmd = (*cmd)->next;
		}
	}
	else
	{
		*cmd = (*cmd)->next;
		(*operators)++;
	}
}
