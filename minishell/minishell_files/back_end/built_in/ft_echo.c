/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 17:43:19 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * This function prints the arguments to the standard output, separated by
 * spaces. If the "-n" flag is provided as the first argument, the newline
 * character is not printed at the end.
 */
void	ft_echo(char **args, t_data *data)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	data->process_status = 0;
	while (!ft_strcmp(args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_printf(args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (flag == false)
		ft_printf("\n");
}
