/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 15:10:27 by gneto-co          #+#    #+#             */
/*   Updated: 2023/10/18 11:55:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	print_di(va_list args)
{
	int	num;

	num = va_arg(args, int);
	ft_putnbr(num);
	return (ft_numlen(num));
}

size_t	print_u(va_list args)
{
	unsigned int	num;
	int				total;

	num = va_arg(args, unsigned int);
	total = ft_put_unsigned_nbr(num, 0);
	return (total);
}

size_t	print_x(va_list args)
{
	unsigned int	num;
	int				total;

	num = va_arg(args, unsigned int);
	total = ft_putnbr_base(num, "0123456789abcdef", 0);
	return (total);
}

size_t	print_xx(va_list args)
{
	unsigned int	num;
	int				total;

	num = va_arg(args, unsigned int);
	total = ft_putnbr_base(num, "0123456789ABCDEF", 0);
	return (total);
}
