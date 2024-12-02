/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expanding_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:38:51 by csilva-r          #+#    #+#             */
/*   Updated: 2024/11/04 18:38:54 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parsing.h"

char	*append_value(char *new_line, char *var_value, char *var_name)
{
	char	*temp;

	temp = ft_strdup(new_line);
	free(new_line);
	new_line = ft_strjoin(temp, var_value + ft_strlen(var_name));
	free(temp);
	return (new_line);
}

char	*append_char(char *new_line, char c)
{
	char	*temp;

	temp = ft_strdup(new_line);
	free(new_line);
	new_line = ft_charjoin(temp, c);
	free(temp);
	return (new_line);
}

/* version of strstr to look for var_name in env */
char	*ft_better_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	if (!big || !little)
		return (NULL);
	i = 0;
	while (big[i] && big[i] == little[i] && i < len)
	{
		i++;
	}
	if (little[i] == '\0')
		return ((char *)(big));
	return (NULL);
}
