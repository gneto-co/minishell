/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 12:09:07 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *
 * 	mod -1 : previous cmd
 * 	mod 1 : next cmd
 *
 */
static t_table_data	*get_cmd(t_data *data, int i, int mod)
{
	int				j;
	t_table_data	*new_cmd;

	new_cmd = NULL;
	j = i;
	while (j > 0)
	{
		j += mod;
		new_cmd = data->table[j];
		if (!new_cmd)
			break ;
		if (new_cmd->type == CMD)
			return (new_cmd);
	}
	return (NULL);
}

/*
 *
 * 	function : connect previous cmd out and next cmd in
 * 	>
 *
 * 	· if !previous cmd or !next cmd
 * 		· error
 * 	· create pipe
 * 	· if !pipe
 * 		· error
 * 	· else
 * 		· prev_cmd out = pipe
 * 		· next_cmd in = pipe
 *
 */
void	ex_pipe(t_data *data, int i)
{
	t_table_data	*prev_cmd;
	t_table_data	*pipe_line;
	t_table_data	*next_cmd;

	if (i == 0)
	{
		data->error = (ft_error(2, "|"), true);
		data->process_status = 2;
		return ;
	}
	prev_cmd = get_cmd(data, i, -1);
	pipe_line = data->table[i];
	next_cmd = get_cmd(data, i, 1);
	if (!next_cmd || !prev_cmd)
	{
		if (data->error == false)
			data->error = (ft_error(2, "|"), true);
	}
	else if (pipe(pipe_line->pipe_fd) == -1)
		data->error = (perror("pipe failed"), true);
	else
	{
		prev_cmd->out_fd = pipe_line->pipe_fd[1];
		next_cmd->in_fd = pipe_line->pipe_fd[0];
	}
}
