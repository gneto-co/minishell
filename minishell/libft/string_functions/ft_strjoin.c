/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 13:48:15 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/29 13:50:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// input: str1, str2
// if str1 and str2,	return a new str: str1 + str2
// if !str1,			return dup of str2
// if !str2,			return dup of str1
// if !str and !char,	return NULL
char	*ft_strjoin(char const *str1, char const *str2)
{
	int		i;
	char	*newstr;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL)
		return (ft_strdup(str2));
	if (str2 == NULL)
		return (ft_strdup(str1));
	i = 0;
	newstr = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (newstr == NULL)
		return (0);
	while (*str1)
	{
		newstr[i++] = *str1;
		str1++;
	}
	while (*str2)
	{
		newstr[i++] = *str2;
		str2++;
	}
	newstr[i] = '\0';
	return (newstr);
}

// input: str1, str2
// if str1 and str2,	return a new str: str1 + str2, free(str1)
// if !str1,			return dup of str2
// if !str2,			return original str1
// if !str and !char,	return NULL
char	*ft_strjoin_free(char const *str1, char const *str2)
{
	int		i;
	char	*newstr;

	if (str1 == NULL && str2 == NULL)
		return (NULL);
	if (str1 == NULL)
		return (ft_strdup(str2));
	if (str2 == NULL)
		return ((char *)str1);
	i = 0;
	newstr = malloc(ft_strlen(str1) + ft_strlen(str2) + 1);
	if (newstr == NULL)
		return (0);
	while (str1[i])
	{
		newstr[i] = str1[i];
		i++;
	}
	while (*str2)
		newstr[i++] = *str2++;
	newstr[i] = '\0';
	free((void *)str1);
	return (newstr);
}

// input: str, cha
// if str and char,		return a new str: str + char
// if !str,				return dup of char
// if !char,			return dup of str
// if !str and !char,	return NULL
char	*ft_str_char_join(const char *str, char c)
{
	int		i;
	char	*newstr;

	if (str == NULL && c == '\0')
		return (NULL);
	if (str == NULL)
		return (ft_strdup(&c));
	if (c == '\0')
		return (ft_strdup(str));
	i = 0;
	newstr = malloc(ft_strlen(str) + 2);
	if (newstr == NULL)
		return (NULL);
	while (*str)
	{
		newstr[i++] = *str;
		str++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	return (newstr);
}

// input: str, cha
// if str and char,		return a new str: str + char, free(str)
// if !str,				return dup of char
// if !char,			return dup of str
// if !str and !char,	return NULL
char	*ft_str_char_join_free(char const *str, char const c)
{
	int		i;
	char	*newstr;

	if (str == NULL && c == '\0')
		return (NULL);
	if (str == NULL)
		return (ft_char_dup(c));
	if (c == '\0')
		return (ft_strdup(str));
	i = 0;
	newstr = malloc(ft_strlen(str) + 2);
	if (newstr == NULL)
		return (NULL);
	while (str[i])
	{
		newstr[i] = str[i];
		i++;
	}
	newstr[i++] = c;
	newstr[i] = '\0';
	free((void *)str);
	return (newstr);
}
