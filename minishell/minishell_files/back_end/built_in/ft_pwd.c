/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env copy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 17:42:14 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Prints the current working directory to the standard output.
 * If successful, the current working directory is printed.
 * If an error occurs, an error message is printed.
 */
void	ft_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	data->process_status = 0;
	if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else
		perror("minishell: getcwd");
}
