/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 10:39:17 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/18 18:17:46 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_clean_house(t_full_cmd *cmd, t_data *data, int status, int temp)
{
	ft_cleanup_list(cmd);
	ft_free_data_temps(data, temp);
	return (status);
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
}

void	ft_cleanup_list(t_full_cmd *cmd)
{
	if (!cmd)
		return ;
	if (cmd->cmd)
		free(cmd->cmd);
	ft_free_tab(cmd->args);
	if (cmd->redirections)
		free(cmd->redirections);
	ft_free_tab(cmd->targets);
	if (cmd->operator)
		free(cmd->operator);
	ft_cleanup_list(cmd->next);
	free(cmd);
}

void	ft_free_data_temps(t_data *data, int temp)
{
	char	*vars_temp;
	char	*heredoc_temp;

	vars_temp = ft_charjoin("/tmp/vars_temp", data->shell_id + '0');
	heredoc_temp = ft_charjoin("/tmp/heredoc_temp", data->shell_id + '0');
	ft_free_tab(data->env);
	rl_clear_history();
	if (temp)
	{
		unlink(vars_temp);
		unlink(heredoc_temp);
	}
	free(vars_temp);
	free(heredoc_temp);
}
