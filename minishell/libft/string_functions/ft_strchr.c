/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:31:16 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/29 11:27:07 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// gets a str and a char
// if that char is on the str
//   return the char position on the str
// if is not
//   return 0
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
