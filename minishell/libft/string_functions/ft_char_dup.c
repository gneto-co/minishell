/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_char_dup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 13:45:51 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/29 13:52:10 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_char_dup(const char c)
{
	char	*new_str;

	if (!c)
		return (NULL);
	new_str = malloc(2);
	if (new_str == NULL)
		return (NULL);
	new_str[0] = c;
	new_str[1] = '\0';
	return (new_str);
}
