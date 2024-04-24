/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 14:46:17 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:33:09 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>
#include <unistd.h>

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	count;
	size_t	i;

	i = 0;
	if (size <= (size_t)ft_strlen(dst))
		return (size + ft_strlen(src));
	count = ft_strlen(dst);
	while (src[i] && count + 1 < size)
	{
		dst[count] = src[i];
		count++;
		i++;
	}
	dst[count] = '\0';
	return (count + ft_strlen(&src[i]));
}
