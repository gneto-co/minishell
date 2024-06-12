/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/21 14:03:51 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/12 13:17:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static int	ft_count_words(char *str, char c)
{
	int	w;

	while ((*str == c || *str == '\n' || *str == 9) && *str)
		str++;
	w = 0;
	while (*str)
	{
		while ((*str != c && *str != '\n' && *str != 9) && *str)
			str++;
		w++;
		while ((*str == c || *str == '\n' || *str == 9) && *str)
			str++;
	}
	return (w);
}

static int	ft_count_letters_of_word(char *str, char c)
{
	int	len;

	len = 0;
	while (str[len])
	{
		if (str[len] == c || str[len] == '\n' || str[len] == 9)
			break ;
		len++;
	}
	return (len);
}

static char	**repartir(char *str, char c, char **lines, int lineslen)
{
	int	i;
	int	j;

	i = 0;
	while (i < lineslen)
	{
		while ((*str == c || *str == '\n' || *str == 9) && *str)
			str++;
		lines[i] = malloc(sizeof(char) * (ft_count_letters_of_word(str, c)
					+ 1));
		if (!lines[i])
		{
			ft_free_array(lines);
			return (NULL);
		}
		j = 0;
		while ((*str != c && *str != '\n' && *str != 9) && *str)
		{
			lines[i][j++] = *str;
			str++;
		}
		lines[i++][j] = '\0';
	}
	lines[i] = NULL;
	return (lines);
}

char	**ft_split(char const *s, char c)
{
	char	*str;
	int		lineslen;
	char	**lines;

	if (!s)
	{
		lines = malloc(sizeof(char *) * 1);
		lines[0] = NULL;
		return (lines);
	}
	str = (char *)s;
	lineslen = ft_count_words(str, c);
	lines = malloc(sizeof(char *) * (lineslen + 1));
	if (lines == NULL)
		return (NULL);
	lines = repartir(str, c, lines, lineslen);
	return (lines);
}
