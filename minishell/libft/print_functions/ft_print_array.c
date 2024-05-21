/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:13:02 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/21 13:52:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
 *  function : print all the elements os a string array
 *  array need to be null terminated
 */
void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	ft_printf("\n--- ft_print_array ---\n");
	while (array[i])
	{
		ft_printf("%s\n", array[i]);
		i++;
	}
	ft_printf("%s\n", array[i]);
	ft_putstr("--- end ---\n");
}
