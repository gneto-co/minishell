/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 19:20:26 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void data_init(t_data *data)
{
	data->error = false;
}

int	main(int ac, char **av, char **env)
{
	char	**array;
	int		i;
	t_data	data;
	(void)	ac;
	(void)	av;

	i = 0;
	data_init(&data);
	array = ft_token_split("  ||abc 'test'_1:|>>>|\"$USER:    $USER ", &data, env);
	if (data.error == false)
	{
		ft_putstr("\n\n");
		while (array[i])
			ft_printf("¦%s¦\n", array[i++]);
		ft_printf("¦%s¦\n", array[i++]);
	}
    ft_free_array(array);
	// lsh_loop(); //NOTE
}
