/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_better_strnstr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 21:26:02 by csilva-r          #+#    #+#             */
/*   Updated: 2024/10/30 21:26:06 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Like strnstr but only looks at the beginning of big string */
char	*ft_better_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;

	i = 0;
	while (big[i] && big[i] == little[i] && i < len)
	{
		i++;
	}
	if (little[i] == '\0')
		return ((char *)(big));
	return (NULL);
}
