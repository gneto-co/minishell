/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/02 18:21:11 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Prints the environment variables to the standard output.
 */
void	ft_env(char **env, t_data *data)
{
	int	i;

	i = 0;
	data->process_status = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_printf("%s\n", env[i++]);
	}
}
