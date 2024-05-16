/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_system_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:54:39 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 17:56:02 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
 * 	function : found a system var and return is content
 * 	for example
 * 		var_name = "SHELL"
 * 		$SHELL = /usr/bin/zsh
 * 		alloc and return "/usr/bin/zsh"
 *
 */
char	*ft_get_system_var(char *var_name, char **env)
{
	char	*str;

	if (!var_name || !env)
		return (NULL);
	str = ft_n_find_on_array(env, var_name, ft_strlen(var_name));
	if (!str)
		return (NULL);
	return (ft_strdup(str + ft_strlen(var_name) + 1));
}
