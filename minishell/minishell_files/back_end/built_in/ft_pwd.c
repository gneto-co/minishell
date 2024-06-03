/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/02 18:21:34 by yadereve         ###   ########.fr       */
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
