/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_less.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:28 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 18:47:23 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *
 * 	function : open file to read and put it on std_in
 * 	>
 *
 * 	· open in file
 * 	· if !in file
 * 		· error
 * 	· else
 * 		· if std_in : close std_in
 * 		· std_in = in_file
 * 
 */
void	ex_less(t_data *data, int i)
{
	int				fd;
	t_table_data	*great;

	great = data->table[i];
	fd = open(great->name, O_RDONLY);
	if (fd == -1)
	{
		data->error = true;
		perror("open file error");
	}
	else
	{
		if (data->in_fd)
			close(data->in_fd);
		data->in_fd = fd;
	}
}
