/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_table.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 11:34:43 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 15:49:59 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	ft_free_table(t_table_data **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		ft_free_array(table[i]->args);
		ft_free_array(table[i]->flags);
		free(table[i]->name);
		free(table[i]);
		i++;
	}
}
