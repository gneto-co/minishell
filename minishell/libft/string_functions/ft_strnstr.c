/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 16:21:28 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:32:47 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *b, const char *l, size_t len)
{
	size_t	h;
	size_t	n;

	h = 0;
	if (l[0] == '\0')
		return ((char *)b);
	while (b[h] && h < len)
	{
		n = 0;
		while (b[h + n] == l[n] && (h + n) < len && l[n])
			n++;
		if (l[n] == '\0')
			return ((char *)b + h);
		h++;
	}
	return (0);
}
