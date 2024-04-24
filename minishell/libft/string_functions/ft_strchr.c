/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:31:16 by gneto-co          #+#    #+#             */
/*   Updated: 2023/10/09 15:51:00 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	char		uc;
	const char	*str;

	uc = (char)c;
	str = (const char *)s;
	while (*str)
	{
		if (*str == uc)
			return ((char *)str);
		str++;
	}
	if (*str == uc)
		return ((char *)str);
	else
		return (0);
}
