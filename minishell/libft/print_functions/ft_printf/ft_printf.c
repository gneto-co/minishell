/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/12 11:02:27 by gneto-co          #+#    #+#             */
/*   Updated: 2023/10/23 15:50:12 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	print_options(va_list args, const char *f)
{
	if (*f == 'd' || *f == 'i')
		return (print_di(args));
	else if (*f == 'c')
		return (print_c(args));
	else if (*f == 's')
		return (print_s(args));
	else if (*f == 'p')
		return (print_p(args));
	else if (*f == 'u')
		return (print_u(args));
	else if (*f == 'x')
		return (print_x(args));
	else if (*f == 'X')
		return (print_xx(args));
	else if (*f == '%')
	{
		ft_putchar('%');
		return (1);
	}
	return (0);
}

int	ft_printf(const char *f, ...)
{
	size_t	printcount;
	va_list	args;

	va_start(args, f);
	printcount = 0;
	if (!f)
		return (-1);
	while (*f)
	{
		if (*f == '%')
		{
			f++;
			printcount += print_options(args, f);
		}
		else
		{
			ft_putchar(*f);
			printcount++;
		}
		f++;
	}
	va_end(args);
	return (printcount);
}

// int	main(void)
// {
// 	char	*str = "abc";
// 	ft_putnbr(printf	("\n|%s|\n",str));
// 	printf("\n------------//------------\n");
// 	ft_putnbr(ft_printf	("\n|%s%3%g%f|\n",str));
// }