/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 19:49:45 by csilva-r          #+#    #+#             */
/*   Updated: 2024/04/30 10:47:19 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	int	count;
	int	i;
	int	check;

	if (!s)
		return (1);
	i = 0;
	count = 0;
	check = 0;
	while (s[i])
	{
		if (s[i] != c && check == 0)
		{
			count++;
			check = 1;
		}
		else if (s[i] == c)
			check = 0;
		i++;
	}
	return (count);
}

static int	find_index(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (i);
}

static char	**free_and_return_null(char **new)
{
	int	i;

	i = 0;
	while (new[i] != NULL)
	{
		free(new[i]);
		i++;
	}
	free(new);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**new;
	int		cut_from;
	int		cut_to;
	int		i;

	new = (char **)malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!new || !s)
		return (NULL);
	i = 0;
	cut_from = 0;
	while (i < count_words(s, c))
	{
		while (s[cut_from] == c)
			cut_from++;
		cut_to = find_index(s + cut_from, c);
		new[i] = (char *)malloc(sizeof(char) * (cut_to + 1));
		if (!new[i])
			return (free_and_return_null(new));
		ft_strlcpy(new[i], s + cut_from, cut_to + 1);
		cut_from += cut_to + 1;
		i++;
	}
	new[i] = NULL;
	return (new);
}
