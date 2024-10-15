/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:39:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/15 11:03:10 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (1);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
	return (0);
}

int	ft_free_cmd(t_full_cmd *cmd)
{
	ft_free_tab(cmd->args);
	free(cmd->redirections);
	ft_free_tab(cmd->targets);
	free(cmd);
	return (0);
}

int	ft_free_ast(t_ast *ast)
{
	t_full_cmd	*cmds;
	t_full_cmd	*temp;

	cmds = *ast->cmds;
	while (cmds->next)
	{
		temp = cmds;
		cmds = cmds->next;
		ft_free_cmd(temp);
	}
	free(ast->cmds);
	ft_free_tab(ast->operators);
	free(ast);
	return (0);
}

int	ft_free_data(t_data *data)
{
	ft_free_tab(data->env);
	rl_clear_history();
	free(data->history);
	data->history = NULL;
	ft_free_ast(data->ast);
	free(data);
	return (0);
}
