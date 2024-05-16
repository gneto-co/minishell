/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 14:22:54 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* initialize data and start reading from terminal */
int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data.env = env;
	data.error = false;
	data.table = NULL;
	ft_readline_loop(&data);
	return (1);
}
