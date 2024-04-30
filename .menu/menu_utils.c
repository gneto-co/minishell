/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 14:39:11 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/12 18:00:36 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "menu.h"

int long	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

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

static char	*sort_char(char *str, char c, va_list args)
{
	char	*new_str;
	char	*num;

	if (c == 'd')
	{
		num = ft_itoa(va_arg(args, int));
		new_str = ft_strjoin(str, num);
		free(num);
	}
	else if (c == 's')
		new_str = ft_strjoin(str, va_arg(args, char *));
	else if (c == 'c')
		new_str = ft_str_char_join(str, va_arg(args, int));
	else
		return (NULL);
	return (new_str);
}

char	*ft_multi_strjoin(const char *source, ...)
{
	va_list	args;
	char	*str;
	char	*temp;

	va_start(args, source);
	if (!source)
		return (NULL);
	str = ft_strdup("");
	while (*source)
	{
		if (*source == '%')
		{
			source++;
			temp = str;
			str = sort_char(str, *source, args);
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
	va_end(args);
	return (str);
}

int	ft_atoi(const char *nptr)
{
	int long	nbr;
	int			sinal;

	nbr = 0;
	sinal = 1;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			sinal = -1;
		nptr++;
	}
	while (*nptr >= '0' && *nptr <= '9')
	{
		nbr *= 10;
		nbr += *nptr - '0';
		nptr++;
	}
	if (nbr * sinal > INT_MAX || nbr * sinal < INT_MIN)
		nbr = 0;
	if (nbr)
		nbr *= sinal;
	return (nbr);
}