/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/02 18:20:59 by yadereve         ###   ########.fr       */
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
