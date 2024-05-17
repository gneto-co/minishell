/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_table.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:23:19 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 11:34:42 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void ft_print_table(t_table_data **table)
{
	int	i;
	int j;
	char *type;
	
	type = NULL;
	i = 0;
	ft_printf("\n╔═══════════════╦═══════════════╦═══════════════╦═══════════════╦═══════════════╗");
	ft_printf("\n║      POS      ║      TYPE     ║  NAME / FILE  ║     FLAGS     ║      ARGS     ║");
	ft_printf("\n╚═══════════════╩═══════════════╩═══════════════╩═══════════════╩═══════════════╝");
	while (table[i])
	{
		ft_printf("\n┌───────────────┬───────────────┬───────────────┬───────────────┬───────────────┐");
		if (table[i]->type == CMD)
		{
			ft_printf("\n│\t%d\t│\tcmd\t│\t%s\t│\t%d\t│\t%d\t│", i, table[i]->name, table[i]->flags_amount, table[i]->args_amount);
			j = 0;
			while (table[i]->flags[j])
			{
				ft_printf("\n├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤");
				ft_printf("\n│\t\t│\t\t│\t\t│\t%s\t│\t\t│", table[i]->flags[j]);
				j++;
			}
			j = 0;
			while (table[i]->args[j])
			{
				ft_printf("\n├───────────────┼───────────────┼───────────────┼───────────────┼───────────────┤");
				ft_printf("\n│\t\t│\t\t│\t\t│\t\t│\t%s\t│", table[i]->args[j]);
				j++;
			}
		}
		else
		{
			     if (table[i]->type == PIPE)
				type = ft_strdup("\tpipe\t");
			else if (table[i]->type == LESS)
				type = ft_strdup("\tless\t");
			else if (table[i]->type == GREAT)
				type = ft_strdup("\tgreat\t");
			else if (table[i]->type == LESSLESS)
				type = ft_strdup("    lessless   ");
			else if (table[i]->type == GREATGREAT)
				type = ft_strdup("   greatgreat  ");
			ft_printf("\n│\t%d\t│%s│\t%s\t│\t\t│\t\t│", i, type, table[i]->name);
			free(type);
		}
		ft_printf("\n└───────────────┴───────────────┴───────────────┴───────────────┴───────────────┘");
		i++;
	}
	ft_printf("\n");
}
