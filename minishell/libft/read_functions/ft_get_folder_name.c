/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_folder_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/09 17:47:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 17:52:54 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

// returns a new str with the actual folder name
char	*ft_get_folder_name(void)
{
	char	cwd[1024];
	char	*new_str;
	char	*last_slash;

	if (getcwd(cwd, sizeof(cwd)) == NULL)
	{
		return (NULL);
	}
	last_slash = ft_strrchr(cwd, '/');
	if (!last_slash)
		new_str = NULL;
	else
		new_str = ft_strdup(last_slash + 1);
	return (new_str);
}
