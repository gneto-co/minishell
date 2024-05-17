/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 16:00:13 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ex_cmd(t_data *data, int i)
{
	char	*cmd_path;

	cmd_path = ft_find_cmd_path(data->table[i]->name, data->env);
	(void)data;
	(void)i;
	ft_printf("\n ex_cmd : %s\n", data->table[i]->name);
	ft_printf("\n cmd_name p : %p\n", data->table[i]->name);
	if (!cmd_path)
	{
		data->error = true;
		ft_error(3, data->table[i]->name);
	}
	else
	{
		ft_printf("\n cmd_path : %s\n", cmd_path);
	}
	free(cmd_path);
}
