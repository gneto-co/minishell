/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:52:37 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/14 00:28:39 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_c(va_list args)
{
	char	c;

	c = (char)va_arg(args, int);
	ft_putchar(c);
	return (1);
}

size_t	print_s(va_list args)
{
	char	*s;

	s = va_arg(args, char *);
	if (!s)
	{
		ft_putstr("(null)");
		return (ft_strlen("(null)"));
	}
	else
	{
		ft_putstr(s);
		return (ft_strlen(s));
	}
}

size_t	print_p(va_list args)
{
	int long	ptr;
	int			total;

	ptr = va_arg(args, long int);
	if (!ptr)
	{
		ft_putstr("(nil)");
		return (5);
	}
	ft_putstr("0x");
	total = ft_putpt(ptr, "0123456789abcdef", 0);
	return (total + 2);
}
