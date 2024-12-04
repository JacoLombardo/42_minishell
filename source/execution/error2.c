/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jalombar <jalombar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 16:34:36 by jalombar          #+#    #+#             */
/*   Updated: 2024/11/20 19:25:53 by jalombar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

int	ft_malloc_error(char *s1, char **tab, int index)
{
	ft_put_error("xmalloc", NULL, "cannot allocate memory\n", 0);
	if (s1)
		free(s1);
	if (tab)
	{
		while (index-- >= 0)
			free(tab[index]);
		free(tab);
	}
	return (1);
}

char	*ft_malloc_error1(char *s1, char **tab, int index)
{
	ft_put_error("xmalloc", NULL, "cannot allocate memory\n", 0);
	if (s1)
		free(s1);
	if (tab)
	{
		while (index-- >= 0)
			free(tab[index]);
		free(tab);
	}
	return (NULL);
}

char	**ft_malloc_error2(char *s1, char **tab, int index)
{
	ft_put_error("xmalloc", NULL, "cannot allocate memory\n", 0);
	if (s1)
		free(s1);
	if (tab)
	{
		while (index-- >= 0)
			free(tab[index]);
		free(tab);
	}
	return (NULL);
}
