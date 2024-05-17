/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 17:35:35 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cmd_process(t_data *data, t_table_data *cmd)
{
	(void)data;
	
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("command process error");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		execve(cmd->path, cmd->args, NULL);
		perror("command process error");
		exit(EXIT_FAILURE);
	}
	else
	{
		// waitpid(cmd->pid, NULL, 0);
	}
}

/*
 *
 * 	function : execute command on table[i] position
 *
 * 	· get command path
 * 	· if command is valid
 * 		· print command
 * 	· if is not
 * 		· error
 * 	· free stuff
 */
void	ex_cmd(t_data *data, int i)
{
	t_table_data	*cmd;

	cmd = data->table[i];
	cmd->path = ft_find_cmd_path(cmd->name, data->env);
	if (cmd->path)
	{
		ft_printf("\n cmd_path : %s\n\n", cmd->path);
		cmd_process(data, cmd);
	}
	else
	{
		data->error = true;
		ft_error(3, cmd->name);
	}
	// free stuff
	free(cmd->path);
}
