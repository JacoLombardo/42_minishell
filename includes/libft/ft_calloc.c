/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:43:25 by csilva-r          #+#    #+#             */
/*   Updated: 2024/04/28 17:42:05 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*new;

	if (size && nmemb > (SIZE_MAX / size))
		return (NULL);
	new = malloc(nmemb * size);
	if (new == 0)
		return (NULL);
	ft_bzero(new, nmemb * size);
	return (new);
}
