/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_multi_strjoin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:39:11 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/14 00:08:35 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static char	*sort(char *str, char c, va_list args)
{
	char	*new_str;
	char	*temp_str;

	if (c == 'd')
	{
		temp_str = ft_itoa(va_arg(args, int));
		new_str = ft_strjoin(str, temp_str);
		free(temp_str);
	}
	else if (c == 's')
	{
		temp_str = va_arg(args, char *);
		if (temp_str)
			new_str = ft_strjoin(str, temp_str);
		else
			new_str = ft_strdup(str);
	}
	else if (c == 'c')
		new_str = ft_str_char_join(str, va_arg(args, int));
	else
		return (NULL);
	return (new_str);
}

static char	*join_all(const char *source, va_list args)
{
	char	*str;
	char	*temp;

	str = ft_strdup("");
	while (*source)
	{
		if (*source == '%')
		{
			source++;
			temp = str;
			str = sort(str, *source, args);
			if (temp != str)
				free(temp);
		}
		else
		{
			temp = str;
			str = ft_str_char_join(str, *source);
			if (temp != str)
				free(temp);
		}
		source++;
	}
	return (str);
}

char	*ft_multi_strjoin(const char *source, ...)
{
	va_list	args;
	char	*str;

	va_start(args, source);
	if (!source)
		return (NULL);
	str = join_all(source, args);
	va_end(args);
	return (str);
}
