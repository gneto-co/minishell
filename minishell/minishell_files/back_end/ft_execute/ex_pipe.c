/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:58 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/12 15:24:44 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	prev_cmd = data->table[i - 1];
	pipe_line = data->table[i];
	next_cmd = data->table[i + 1];
	if (prev_cmd->type != CMD || !next_cmd || next_cmd->type != CMD) // FIXME faz o commando: cat | << e0f
		data->error = (ft_error(2, "|"), true);
	else if (pipe(pipe_line->pipe_fd) == -1)
		data->error = (perror("pipe failed"), true);
	else
	{
		prev_cmd->out_fd = pipe_line->pipe_fd[1];
		next_cmd->in_fd = pipe_line->pipe_fd[0];
	}
}
