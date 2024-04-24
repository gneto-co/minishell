/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:15 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/13 23:50:44 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*newstr;

	i = 0;
	newstr = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (newstr == NULL)
		return (0);
	while (*s1)
	{
		newstr[i] = *s1;
		i++;
		s1++;
	}
	while (*s2)
	{
		newstr[i] = *s2;
		i++;
		s2++;
	}
	newstr[i] = '\0';
	return (newstr);
}

char	*ft_str_char_join(char *str, char c)
{
	int		i;
	char	*new_str;

	i = 0;
	if (str)
	{
		new_str = malloc(ft_strlen(str) + 2);
		if (!new_str)
			return (NULL);
		while (str[i])
		{
			new_str[i] = str[i];
			i++;
		}
	}
	else
	{
		new_str = malloc(2);
		return (NULL);
	}
	new_str[i] = c;
	i++;
	new_str[i] = '\0';
	return (new_str);
}
