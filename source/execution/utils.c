/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/11 13:51:59 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

char	*ft_free_cmd(t_cmd *cmd)
{
	ft_free_tab(cmd->args);
	free(cmd->redirection);
	free(cmd->target);
	free(cmd);
	return (NULL);
}

char	*ft_free_ast(t_ast *ast)
{
	int		i;
	t_cmd	*cmds;
	t_cmd	*temp;

	i = 0;
	cmds = *ast->cmds;
	while (cmds->next)
	{
		temp = cmds;
		cmds = cmds->next;
		ft_free_cmd(temp);
	}
	while (ast->operators[i])
	{
		free(ast->operators[i]);
		i++;
	}
	free(ast->input);
	free(ast);
	return (NULL);
}

char	*ft_free_data(t_data *data)
{
	int	i;

	i = 0;
	while (data->env[i])
	{
		free(data->env[i]);
		i++;
	}
	free(data->env);
	i = 0;
	while (data->history[i])
	{
		free(data->history[i]);
		i++;
	}
	free(data->history);
	free(data);
	return (NULL);
}

int	ft_find_var(char *env, char *name)
{
	int		j;
	char	*sub;

	j = 0;
	while (env[j] && env[j] != '=')
		j++;
	sub = ft_substr(env, 0, j);
	if (!ft_strcmp(sub, name))
	{
		free(sub);
		return (j + 1);
	}
	else
	{
		free(sub);
		return (0);
	}
}
