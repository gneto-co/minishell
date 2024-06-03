/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 11:25:24 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/03 11:02:32 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

/*
 *
 *  Function : put all array content in a file separated by '\n'
 *  · array need to be null terminated
 *
 *
 */
void	ft_array_to_file(char **array, char *file_name)
{
	int	i;
	int	fd;

	i = 0;
	fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return ;
	while (array[i])
	{
		write(fd, array[i], ft_strlen(array[i]));
		i++;
		if (array[i])
			write(fd, "\n", 1);
	}
	close(fd);
}

/*
 *
 *  Function : read all content from a file and put each line in a **array
 *
 *
 */
char	**ft_file_to_array(char *file_name)
{
	int		fd;
	char	**array;
	char	*new_str;
	char	*temp_str;

	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (NULL);
	new_str = NULL;
	array = NULL;
	while (1)
	{
		temp_str = get_next_line(fd);
		if (!temp_str)
			break ;
		new_str = ft_strjoin_free(new_str, temp_str);
		free(temp_str);
	}
	array = ft_split(new_str, '\n');
	free(new_str);
	close(fd);
	return (array);
}
