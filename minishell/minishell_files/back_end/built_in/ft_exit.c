/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:47 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/06 11:52:46 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * This function is responsible for exiting the program with a specified exit
 * code. It takes an array of arguments and a pointer to a data structure as
 * parameters. The function checks if the first argument is a valid numeric
 * value and sets the exit code accordingly. If the first argument is not a
 * valid numeric value, it prints an error message to the standard error and
 * sets the exit code to 255. If there are more than one argument, it prints
 * an error message to the standard error and sets the exit code to 1.
 * If the first argument is a valid numeric value and there are no more
 * arguments, it sets the exit code to the converted value and sets the exit
 * flag to true. If there are no arguments, it sets the exit flag to true.
 */
void	ft_exit(char **args, t_data *data)
{
	int	i;

	i = -1;
	data->process_status = 0;
	ft_printf("exit\n");
	while (args[1] && args[1][++i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putendl_fd(" numeric argument required", STDERR_FILENO);
			data->process_status = 255;
			break ;
		}
		else if (args[1][i + 1] == '\0' && args[2])
		{
			ft_putendl_fd(" too many arguments", STDERR_FILENO);
			data->process_status = 1;
			break ;
		}
		else if (args[1][i + 1] == '\0')
		{
			data->process_status = ft_atoi(args[1]);
			data->exit = true;
		}
	}
	if (args[0])
		data->exit = true;
}
