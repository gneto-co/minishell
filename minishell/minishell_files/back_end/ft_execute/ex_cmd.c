/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 18:45:30 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cmd_process(t_data *data, t_table_data *cmd)
{
	char	*envp[2];

	envp[0] = ft_strdup("TERM=xterm");
	envp[1] = NULL;
	// test
	// cmd->in_fd = open("in1", O_RDONLY);
	// if (cmd->in_fd == -1)
	// {
	// 	perror("open file error");
	// }
	// test end
	(void)data;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("command process error");
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
	{
		if (cmd->in_fd)
		{
			dup2(cmd->in_fd, STDIN_FILENO);
			close(cmd->in_fd);
		}
		if (cmd->out_fd)
		{
			dup2(cmd->out_fd, STDOUT_FILENO);
			close(cmd->out_fd);
		}
		execve(cmd->path, cmd->args, envp);
		perror("command process error");
		exit(EXIT_FAILURE);
	}
	free(envp[0]);
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
		// ft_printf("\n cmd_path : %s\n\n", cmd->path);
		if (data->in_fd)
			cmd->in_fd = data->in_fd;
		if (data->out_fd)
			cmd->out_fd = data->out_fd;
		cmd_process(data, cmd);
	}
	else
	{
		data->error = true;
		ft_error(3, cmd->name);
	}
	free(cmd->path);
}
