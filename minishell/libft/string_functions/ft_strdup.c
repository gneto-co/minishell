/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:18:11 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:33:22 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *src)
{
	char	*aa;
	char	*rtrn;
	int		i;

	i = 0;
	while (src[i])
		i++;
	aa = (char *)malloc((i + 1) * sizeof(char));
	if (aa == NULL)
		return (NULL);
	rtrn = aa;
	while (*src)
	{
		*aa = *src;
		aa++;
		src++;
	}
	*aa = '\0';
	return (rtrn);
}

// por entre a linha 21 e 22
// if (!src)
// 	return (NULL);