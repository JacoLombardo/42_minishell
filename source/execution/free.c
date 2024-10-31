/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:39:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/31 19:54:19 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

void	ft_free_both_tab(char **tab1, char **tab2)
{
	ft_free_tab(tab1);
	ft_free_tab(tab2);
}

void	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	tab = NULL;
}

void	ft_free_cmd(t_full_cmd *cmd)
{
	t_full_cmd *temp;

	temp = NULL;
	while (cmd)
	{
		if (cmd->next)
			temp = cmd->next;
		else
			temp = NULL;
		free(cmd->cmd);
		ft_free_tab(cmd->args);
		if (cmd->redirections)
			free(cmd->redirections);
		ft_free_tab(cmd->targets);
		if (cmd->operator)
			free(cmd->operator);
		free(cmd);
		cmd = temp;
	}
}

void	ft_free_data_temps(t_data *data)
{
	ft_free_tab(data->env);
	rl_clear_history();
	unlink("/tmp/heredoc_temp");
	unlink("/tmp/vars_temp");
}

// void	ft_free_ast(t_ast *ast)
// {
// 	t_full_cmd	*cmds;
// 	t_full_cmd	*temp;

// 	cmds = *ast->cmds;
// 	while (cmds->next)
// 	{
// 		temp = cmds;
// 		cmds = cmds->next;
// 		ft_free_cmd(temp);
// 	}
// 	free(ast->cmds);
// 	ft_free_tab(ast->operators);
// 	free(ast);
// }