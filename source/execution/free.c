/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:39:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/18 11:31:48 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_free_reachable(t_full_cmd *cmd, t_data *data)
{
	ft_free_cmd(cmd);
	ft_free_tab(data->env);
	return (1);
}

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
	t_full_cmd	*temp;

	temp = NULL;
	while (cmd)
	{
		if (cmd->next)
			temp = cmd->next;
		else
			temp = NULL;
		//free(cmd->cmd);
		ft_free_tab(cmd->args);
		if (cmd->redirections)
			free(cmd->redirections);
		ft_free_tab(cmd->targets);
		if (cmd->operator)
			free(cmd->operator);
		//free(cmd);
		cmd = temp;
	}
}

void	ft_free_data_temps(t_data *data)
{
	char	*vars_temp;
	char	*heredoc_temp;

	vars_temp = ft_charjoin("/tmp/vars_temp", data->shell_id + '0');
	heredoc_temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
	ft_free_tab(data->env);
	rl_clear_history();
	unlink(vars_temp);
	unlink(heredoc_temp);
	free(vars_temp);
	free(heredoc_temp);
}
