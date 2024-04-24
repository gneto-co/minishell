/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 15:06:08 by gneto-co          #+#    #+#             */
/*   Updated: 2023/10/06 09:28:46 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	uc;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)s;
	uc = (unsigned char)c;
	while (i < n)
	{
		ptr[i] = uc;
		i++;
	}
	return (s);
}
