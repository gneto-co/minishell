/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 09:18:11 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/01 12:27:39 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strdup(const char *str)
{
	char	*aa;
	char	*rtrn;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i])
		i++;
	aa = (char *)malloc((i + 1) * sizeof(char));
	if (aa == NULL)
		return (NULL);
	rtrn = aa;
	while (*str)
	{
		*aa = *str;
		aa++;
		str++;
	}
	*aa = '\0';
	return (rtrn);
}

/*
 *  function : dup a array and all is content
 *  array need to be null terminated
 */
char	**ft_array_dup(char **array)
{
	char	**new_array;
	int		i;

	if (!array)
		return (NULL);
	i = 0;
	new_array = malloc(sizeof(char *) * (ft_arraylen(array) + 1));
	if (!new_array)
		return (NULL);
	while (array[i])
	{
		new_array[i] = ft_strdup(array[i]);
		i++;
	}
	new_array[i] = NULL;
	return (new_array);
}
