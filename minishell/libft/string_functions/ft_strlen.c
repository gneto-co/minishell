/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 15:33:38 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/30 16:47:19 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int long	ft_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int long	ft_arraylen(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}
