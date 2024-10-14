/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_dispatch.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: csilva-r <csilva-r@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 19:00:32 by csilva-r          #+#    #+#             */
/*   Updated: 2024/05/06 15:54:25 by csilva-r         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int     pf_putunbr(unsigned int n, char *charset, int counter)
{
        unsigned int            base;

        base = ft_strlen(charset);
        if (n <= base - 1)
                counter = pf_putchar(charset[n % base], counter);
        else
        {
                counter = pf_putunbr(n / base, charset, counter);
                counter = pf_putchar(charset[n % base], counter);
        }
        return (counter);
}

int     pf_putstr(char *s, int counter)
{
        int     i;

        if (!s)
        {
                counter = pf_putstr("(null)", counter);
                return (counter);
        }
        i = 0;
        while (s[i] != '\0')
        {
                counter = pf_putchar(s[i], counter);
                i++;
        }
        return (counter);
}

int     pf_putptr(unsigned long long ptr, char *charset, int counter)
{
        unsigned long long              base;

        if ((void *)ptr == NULL)
        {
                counter = pf_putstr("(nil)", counter);
                return (counter);
        }
        base = ft_strlen(charset);
        if (ptr <= base - 1)
                counter = pf_putchar(charset[ptr % base], counter);
        else
        {
                counter = pf_putptr(ptr / base, charset, counter);
                counter = pf_putchar(charset[ptr % base], counter);
        }
        return (counter);
}

int     pf_putnbr(int n, char *charset, int counter, int sign_matters)
{
        long    ln;
        int             base;

        if (sign_matters == 0 && n < 0)
                ln = n * -1;
        else
                ln = n;
        base = ft_strlen(charset);
        if (ln < 0)
        {
                counter = pf_putchar('-', counter);
                ln *= -1;
        }
        if (ln <= base - 1)
                counter = pf_putchar(charset[ln % base], counter);
        else
        {
                counter = pf_putnbr(ln / base, charset, counter, 0);
                counter = pf_putchar(charset[ln % base], counter);
        }
        return (counter);
}

int     pf_putchar(char c, int counter)
{
        write(1, &c, 1);
        counter++;
        return (counter);
}


