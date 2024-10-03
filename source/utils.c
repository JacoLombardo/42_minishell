/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/03 11:44:42 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	free(cmd->cmd);
	ft_free_tab(cmd->args);
	ft_free_tab(cmd->options);
	free(cmd);
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