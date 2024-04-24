/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nb_already_exist.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 15:24:02 by gabriel           #+#    #+#             */
/*   Updated: 2023/11/21 15:01:05 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_nb_already_exist(int *nb_list, int nb, size_t size)
{
	size_t	i;

	i = 0;
	while (i < size)
	{
		if (nb_list[i] == nb)
			return (1);
		i++;
	}
	return (0);
}
