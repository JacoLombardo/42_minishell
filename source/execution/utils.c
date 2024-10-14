/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/10/14 10:39:32 by jalombar         ###   ########.fr       */
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
