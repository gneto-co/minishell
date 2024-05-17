/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_greatgreat.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:41 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 18:29:48 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *
 * 	function : open file to write on append mod and put it on std_out
 * 	>>
 *
 * 	· open out file
 * 	· if !out file
 * 		· error
 * 	· else
 * 		· if std_out : close std_out
 * 		· std_out = out_file
 * 
 */
void	ex_greatgreat(t_data *data, int i)
{
	int				fd;
	t_table_data	*great;

	great = data->table[i];
	fd = open(great->name, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
	{
		data->error = true;
		perror("open file error");
	}
	else
	{
		if (data->out_fd)
			close(data->out_fd);
		data->out_fd = fd;
	}
}
