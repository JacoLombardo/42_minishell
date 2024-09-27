/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 18:55:03 by csilva-r          #+#    #+#             */
/*   Updated: 2024/05/04 18:56:54 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

static int     arg_dispatch(const char c, va_list args, int count)
{
        void    *ptr;

        if (c == 'c')
                count = pf_putchar(va_arg(args, int), count);
        else if (c == 's')
                count = pf_putstr(va_arg(args, char *), count);
        else if (c == 'd' || c == 'i')
                count = pf_putnbr(va_arg(args, int), DEC_BASE, count, 1);
        else if (c == 'u')
                count = pf_putunbr(va_arg(args, unsigned int), DEC_BASE, count);
        else if (c == 'x')
                count = pf_putunbr(va_arg(args, unsigned int), HEX_BASE_LOW, count);
        else if (c == 'X')
                count = pf_putunbr(va_arg(args, unsigned int), HEX_BASE_UPP, count);
        else if (c == 'p')
        {
                ptr = va_arg(args, void *);
                if (ptr != NULL)
                        count = pf_putstr("0x", count);
                count = pf_putptr((unsigned long)ptr, HEX_BASE_LOW, count);
        }
        else if (c == '%')
                count = pf_putchar('%', count);
        return (count);
}


int	ft_printf(const char *input, ...)
{
	va_list	args;
	int		counter;
	int		i;

	if (!input)
		return (0);
	i = 0;
	counter = 0;
	va_start(args, input);
	while (input[i])
	{
		if (input[i] == '%')
		{
			if (input[i + 1])
			{
				counter = arg_dispatch(input[i + 1], args, counter);
				i++;
			}
			else
				return (-1);
		}
		else
			counter = pf_putchar(input[i], counter);
		i++;
	}
	va_end(args);
	return (counter);
}
