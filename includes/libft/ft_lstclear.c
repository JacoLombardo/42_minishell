/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 16:06:31 by csilva-r          #+#    #+#             */
/*   Updated: 2024/04/29 16:33:02 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*i;
	t_list	*next;

	if (!lst || !del)
		return ;
	i = *lst;
	while (i)
	{
		next = i->next;
		ft_lstdelone(i, del);
		i = next;
	}
	*lst = NULL;
}
