/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/03 16:44:21 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**array;
	int		i;

	i = 0;
	array = ft_token_split("'a''a'", env);
	// array = ft_token_split(">>00> $PAGER 00", env);
	ft_putstr("\n\n");
	while (array[i])
		ft_printf("¦%s¦\n", array[i++]);
	ft_printf("¦%s¦\n", array[i++]);
    ft_free_array(array);
}
