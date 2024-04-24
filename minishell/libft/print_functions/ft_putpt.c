/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putpt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 11:56:26 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:35:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_putpt(unsigned long int nbr, char *base, int total)
{
	int		bl;
	char	c;

	bl = ft_strlen(base);
	if ((nbr / bl) > 0)
	{
		total = ft_putpt(nbr / bl, base, total);
		total = ft_putpt(nbr % bl, base, total);
	}
	else
	{
		c = base[nbr];
		total += write(1, &c, 1);
	}
	return (total);
}
