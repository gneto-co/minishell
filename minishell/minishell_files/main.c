/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/13 17:05:44 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// that function initialize all vars if t_data
static void	data_init(t_data *data)
{
	data->error = false;
}

// ft_get_user_input()
int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data);
	ft_readline_loop(&data, env);
	return (1);
}
