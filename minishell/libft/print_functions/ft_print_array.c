/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:13:02 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/05 16:02:19 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
 *  function : print all the elements os a string array
 *  array need to be null terminated
 */
void	ft_print_array_tester(char **array)
{
	int	i;

	i = 0;
	ft_printf("\n%s------ ft_print_array ------%s\n", "\033[31m\033[33m",
		"\033[0m");
	if (!array)
		ft_printf("!array");
	else
	{
		while (array[i])
		{
			ft_printf("%sarray[%d]%s\n", "\033[31m\033[33m", i, "\033[0m");
			ft_printf("%s\n", array[i]);
			i++;
		}
		ft_printf("%sarray[%d]%s\n", "\033[31m\033[33m", i, "\033[0m");
		ft_printf("%s\n", array[i]);
	}
	ft_printf("%s------ end ------%s\n", "\033[31m\033[33m", "\033[0m");
}

void	ft_print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (array)
	{
		while (array[i])
		{
			ft_putstr_fd(array[i], 1);
			ft_putstr_fd("\n", 1);
			i++;
		}
	}
}

void	ft_print_array_fd(char **array, int fd)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	if (array)
	{
		while (array[i])
		{
			ft_putstr_fd(array[i], fd);
			ft_putstr_fd("\n", fd);
			i++;
		}
	}
}
