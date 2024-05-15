/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:23:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 14:56:23 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static	void ft_free_table(t_table_data **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		ft_free_array(table[i]->args);
		ft_free_array(table[i]->flags);
		free(table[i]);
		i++;
	}
}

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
	// convert user input to a command table
	//
	table = create_cmd_table(array_user_input, data);
	//
	// TODO : execute cmd_table
	//
	if (data->error == false)
	{
		ft_print_table(table);
	}
	//
	// free stuff
	//
	ft_free_table(table);
	free(table);
	//
	// end
	//
	return (0);
}
