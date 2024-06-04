/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:13:02 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/03 08:48:38 by gneto-co         ###   ########.fr       */
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
	ft_printf("\n%s------ ft_print_array ------%s\n","\033[31m\033[33m","\033[0m");
	if (!array)
		ft_printf("!array");
	else
	{
		while (array[i])
		{
			ft_printf("%sarray[%d]%s\n","\033[31m\033[33m", i,"\033[0m");
			ft_printf("%s\n", array[i]);
			i++;
		}
		ft_printf("%sarray[%d]%s\n","\033[31m\033[33m", i,"\033[0m");
		ft_printf("%s\n", array[i]);
	}
	ft_printf("%s------ end ------%s\n","\033[31m\033[33m","\033[0m");
}
