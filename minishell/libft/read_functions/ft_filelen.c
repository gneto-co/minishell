/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_filelen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 14:23:24 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/01 11:45:12 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
 *
 *  Function : return the amount of lines in a file
 *
 *
 */
size_t	ft_filelen(char *file_name)
{
	int		i;
	int		fd;
	char	*str;

	fd = open(file_name, O_RDONLY);
	if (!fd)
		return (-1);
	i = 0;
	while (1)
	{
		str = get_next_line(fd);
		if (!str)
			break ;
		free(str);
		i++;
	}
	close(fd);
	return (i);
}
