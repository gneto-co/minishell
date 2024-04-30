/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 10:45:41 by gneto-co          #+#    #+#             */
/*   Updated: 2023/11/28 13:42:57 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "stdio.h"

char	*get_next_line(int fd)
{
	static char		buffer [BUFFER_SIZE + 1];
	char			*str;
	int				i;

	i = 0;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
	{
		while (i <= BUFFER_SIZE)
			buffer[i++] = '\0';
		return (NULL);
	}
	str = NULL;
	while (buffer[0] || read(fd, buffer, BUFFER_SIZE) > 0)
	{
		str = ft_strjoin_gnl(str, buffer);
		buffer_clean_gnl(buffer);
		if (str[ft_linelen_gnl(str) - 1] == '\n')
			return (str);
	}
	return (str);
}

// #include <fcntl.h>
// int main(void)
// {
// 	int		fd;
// 	char	*a;

// 	fd = open("txt/little.txt", O_RDONLY);

// 	while (a)
// 	{
// 		printf("\033[47;30m$\033[0m");
// 		a = get_next_line(fd);
// 		printf("%s", a);
// 		free(a);
// 		printf("\033[47;30m$\033[0m");
// 		printf("\n\n");
// 	}

// 	close(fd);
// 	return (0);
// }