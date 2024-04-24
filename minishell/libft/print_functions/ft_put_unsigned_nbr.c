/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_unsigned_nbr.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:39:57 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:35:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_put_unsigned_nbr(unsigned int n, int total)
{
	char	c;

	if ((n / 10) > 0)
	{
		total = ft_put_unsigned_nbr(n / 10, total);
		total = ft_put_unsigned_nbr(n % 10, total);
	}
	else
	{
		c = n + '0';
		total += write(1, &c, 1);
	}
	return (total);
}
