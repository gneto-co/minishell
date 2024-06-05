/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/05 15:11:57 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

/*
 *
 * 	· if cmd is builtin
 * 		· execute command on parent
 * 	· else
 * 		· execute command on child
 */
static void	builtin_selector(t_data *data, t_table_data *cmd)
{
	if (!ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "cd")
		|| !ft_strcmp(cmd->name, "pwd") || !ft_strcmp(cmd->name, "export")
		|| !ft_strcmp(cmd->name, "unset") || !ft_strcmp(cmd->name, "env")
		|| !ft_strcmp(cmd->name, "exit"))
	{
		parent_process_builtin_cmd(data, cmd);
	}
	else
		parent_process_basic_cmd(data, cmd);
}

/*
 *
 * 	function : execute command on table[i] position
 *
 * 	· get command path
 * 	· if command is valid
 * 		· check for redirection
 * 		· execute cmd
 * 	· if is not
 * 		· error
 * 	· free stuff
 */
void	ex_cmd(t_data *data, int i)
{
	t_table_data	*cmd;

	cmd = data->table[i];
	cmd->path = ft_find_cmd_path(cmd->name, data->env);
	if (data->infile_error == true)
		data->infile_error = false;
	else if (cmd->path)
	{
		if (!cmd->in_fd && data->in_fd)
			cmd->in_fd = data->in_fd;
		if (!cmd->out_fd && data->out_fd)
			cmd->out_fd = data->out_fd;
		builtin_selector(data, cmd);
	}
	else
	{
		data->error = true;
		ft_error(3, cmd->name);
		data->process_status = 127;
	}
	free(cmd->path);
}
