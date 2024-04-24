/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_on_array.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 09:26:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/09 09:48:19 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// receive an array of strings (null terminated) and a string
// return a pointer to the first string on array thats
// equal to the given string
// if theres is no str equal return NULL
char	*ft_find_on_array(char **array, char *str)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strcmp(array[i], str))
			return (array[i]);
		i++;
	}
	return (NULL);
}

// receive an array of strings (null terminated) and a string
// return a pointer to the first string on array thats
// equal to the given string
// if theres is no str equal return NULL
char	*ft_n_find_on_array(char **array, char *str, int n)
{
	int	i;

	i = 0;
	while (array[i])
	{
		if (!ft_strncmp(array[i], str, n))
			return (array[i]);
		i++;
	}
	return (NULL);
}
