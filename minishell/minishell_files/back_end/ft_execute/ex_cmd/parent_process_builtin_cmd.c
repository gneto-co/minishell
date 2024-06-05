/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_builtin_cmd.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/05 16:17:27 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	final_cmd_execute(t_data *data, t_table_data *cmd)
{
	if (!ft_strcmp(cmd->name, "env"))
		ft_env(data->env, data);
	else if (!ft_strcmp(cmd->name, "export"))
		ft_export(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd->args, data);
}

static void	output_manager(t_data *data, t_table_data *cmd)
{
	// if (!ft_strcmp(cmd->name, "pwd"))
	// {
	// 	data->output_string = ft_strdup("batatinhas fritas");
	// }
	if (!ft_strcmp(cmd->name, "echo") || !ft_strcmp(cmd->name, "pwd")
		|| !ft_strcmp(cmd->name, "export") || !ft_strcmp(cmd->name, "env"))
	{
		if (!cmd->out_fd)
			cmd->out_fd = 1;
		ft_putstr_fd(data->output_string, cmd->out_fd);
		free(data->output_string);
		if (cmd->in_fd)
			close(cmd->in_fd);
		if (cmd->out_fd && cmd->out_fd != 1)
			close(cmd->out_fd);
	}
}

/*
 *
 * 	· execute cmd
 * 	· close pipe / redirection
 * 	· error management
 */
void	parent_process_builtin_cmd(t_data *data, t_table_data *cmd)
{
	// ft_printf("BUILTIN COMMAND START\n");
	final_cmd_execute(data, cmd);
	output_manager(data, cmd);
	// ft_printf("BUILTIN COMMAND END\n");
}
