/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:23:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 13:28:47 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_execute(char **array_user_input, t_data *data, char **env)
{
	int				i;
	t_table_data	**table;

	(void)data;
	(void)env;
	(void)i;
	//
	// initialize data
	//
	i = 0;
	//
	// LEAK
	// convert user_in to cmd_table
	//
	table = create_cmd_table(array_user_input);
	ft_print_table(table);
	//
	// TODO : execute cmd_table
	//
	//
	// free stuff
	//
	return (0);
}
