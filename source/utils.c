/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 11:11:21 by jalombar          #+#    #+#             */
/*   Updated: 2024/09/30 16:08:32 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while (matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
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
