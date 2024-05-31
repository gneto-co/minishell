/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:37:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 17:38:20 by gneto-co         ###   ########.fr       */
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
