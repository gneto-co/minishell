/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:18:11 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/30 16:07:23 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *str)
{
	char	*aa;
	char	*rtrn;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	aa = (char *)malloc((i + 1) * sizeof(char));
	if (aa == NULL)
		return (NULL);
	rtrn = aa;
	while (*str)
	{
		*aa = *str;
		aa++;
		str++;
	}
	*aa = '\0';
	return (rtrn);
}

// por entre a linha 21 e 22
// if (!src)
// 	return (NULL);