/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 10:07:26 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:32:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*free_void_spaces(char *new_str)
{
	char	*final_str;

	final_str = ft_strdup(new_str);
	free(new_str);
	return (final_str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	int		i;
	int		j;

	if (len == 0)
	{
		new_str = (char *)malloc(1);
		new_str[0] = '\0';
		return (new_str);
	}
	if (len > (size_t)ft_strlen(s))
	{
		len = (size_t)(ft_strlen(s) + 1);
	}
	new_str = (char *)malloc((int long)(len + 1));
	if (!s || !new_str)
		return (0);
	i = start;
	j = 0;
	while (i < ft_strlen(s) && j < (int)len)
		new_str[j++] = s[i++];
	new_str[j] = '\0';
	return (free_void_spaces(new_str));
}
