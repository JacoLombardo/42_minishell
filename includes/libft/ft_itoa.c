/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 16:16:55 by csilva-r          #+#    #+#             */
/*   Updated: 2024/04/28 19:16:20 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count = 1;
	while (n != 0)
	{
		count++;
		n = n / 10;
	}
	return (count);
}

static void	populate(int i, int length, int n, char *new)
{
	int	count;

	count = length - 1;
	if (n < 0)
	{
		n *= -1;
		new[0] = '-';
	}
	while (i < length)
	{
		new[count] = (n % 10) + '0';
		n /= 10;
		count--;
		i++;
	}
	new[length] = '\0';
}

char	*ft_itoa(int n)
{
	int		i;
	int		length;
	char	*new;

	if (n == INT_MIN)
		return (ft_strdup("-2147483648"));
	length = count_digits(n);
	i = 0;
	if (n < 0)
	{
		i = 1;
		length++;
	}
	new = (char *)malloc(sizeof(char) * (length + 1));
	if (!new)
		return (NULL);
	populate(i, length, n, new);
	return (new);
}
