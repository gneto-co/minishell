/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_lessless.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:25 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 18:06:35 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_write_text(char *stop_str)
{
	char	*input;
	char	*str;

	str = NULL;
	while (1)
	{
		input = readline("> ");
		if (!input || ft_strcmp(input, stop_str) == 0)
		{
			free(input);
			ft_printf("\n");
			break ;
		}
		else
			str = ft_strjoin_free(str, input);
		str = ft_strjoin_free(str, "\n");
		free(input);
	}
	return (str);
}

/*
 *
 * 	function : create and get a msg to a temp file,
		then open file to read and put it on std_in
 * 	<<
 *
 * 	· create/open temp file
 * 	· if !temp file
 * 		· error
 * 	· else
 * 		· get user input text
 * 		· put text on temp file
 *
 * 	· open temp file
 * 	· if !temp file
 * 		· error
 * 	· else
 * 		· if std_in : close std_in
 * 		· std_in = temp file
 */
void	ex_lessless(t_data *data, int i)
{
	int				fd;
	char			*str;
	t_table_data	*lessless;

	lessless = data->table[i];
	fd = open(LESSLESS_TEMP_FILE, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		data->infile_error = (perror("open file error"), true);
	else
	{
		str = get_write_text(lessless->name);
		write(fd, str, ft_strlen(str));
		free(str);
		close(fd);
	}
	fd = open(LESSLESS_TEMP_FILE, O_RDONLY);
	if (fd == -1)
		data->infile_error = (perror("open file error"), true);
	else
	{
		if (data->in_fd)
			close(data->in_fd);
		data->in_fd = fd;
	}
}
