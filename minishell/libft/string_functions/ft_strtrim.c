/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/11 08:44:51 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/02 19:32:40 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdio.h>

static int	ft_char_on_str(char c, char *str)
{
	while (*str)
	{
		if (*str == c)
			return (1);
		str++;
	}
	return (0);
}

static char	*free_void_spaces(char *new_str)
{
	char	*final_str;

	final_str = ft_strdup(new_str);
	free(new_str);
	return (final_str);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*new_str;
	int		i;
	int		j;
	int		s1_len;

	i = 0;
	j = 0;
	s1_len = ft_strlen(s1);
	new_str = (char *)malloc(s1_len + 1);
	if (!s1 || !new_str)
		return (0);
	while (ft_char_on_str(s1[i], (char *)set))
		i++;
	if (i == (s1_len))
	{
		*new_str = '\0';
		return (free_void_spaces(new_str));
	}
	while (s1[i])
		new_str[j++] = s1[i++];
	while (ft_char_on_str(s1[--i], (char *)set))
		j--;
	new_str[j] = '\0';
	return (free_void_spaces(new_str));
}
