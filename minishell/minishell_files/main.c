/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/06 10:22:07 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	**array;
	int		i;
	(void)	ac;
	(void)	av;

	i = 0;
	array = ft_token_split(">>00> $PAGER 00", env);
	while (array[i])
		ft_printf("'%s'\n", array[i++]);
	ft_printf("'%s'\n", array[i++]);
    ft_free_array(array);

	lsh_loop(); //NOTE
}
