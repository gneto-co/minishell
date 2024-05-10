/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_path.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:47:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 17:53:38 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// returns a new str with the actual folder name
char	*ft_get_path(void)
{
	char	cwd[1024];
	char	*new_str;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		return (NULL);
	}
	new_str = ft_strdup(cwd);
	return (new_str);
}
