/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 14:39:57 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:33:36 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	char		c;
	int long	l;

	if (fd < 0)
		return ;
	l = n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l *= -1;
	}
	if (l > 9)
	{
		c = '0' + l % 10;
		ft_putnbr_fd(l / 10, fd);
		ft_putchar_fd(c, fd);
	}
	else
	{
		c = l + '0';
		ft_putchar_fd(c, fd);
	}
}
