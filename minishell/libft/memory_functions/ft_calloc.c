/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 08:33:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:34:42 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*line;

	if (nmemb == 0 && size == 0)
		return (malloc(1));
	else if (nmemb == 0 || size == 0)
		return (NULL);
	line = malloc(nmemb * size);
	if (line == NULL)
		return (NULL);
	ft_memset(line, 0, nmemb * size);
	return (line);
}
