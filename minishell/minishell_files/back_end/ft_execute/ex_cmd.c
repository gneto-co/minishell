/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ex_cmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 18:26:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	final_cmd_execute(t_data *data, t_table_data *cmd, char **envp)
{
	if (!ft_strcmp(cmd->name, "cd"))
		ft_cd(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "env"))
		ft_env(data->env, data);
	else if (!ft_strcmp(cmd->name, "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(cmd->name, "echo"))
		ft_echo(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "export"))
		ft_export(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "unset"))
		ft_unset(cmd->args, data);
	else if (!ft_strcmp(cmd->name, "exit"))
		ft_exit(cmd->args, data);
	else
	{
		data->process_status = execve(cmd->path, cmd->args, envp);
		perror("command process error");
		data->error = true;
	}
	// TODO : temp_file = data->env
	exit(0);
}

/*
 *
 * 	· configure pipe / redirection
 * 	· execute cmd
 * 	· error management
 */
static void	child_process(t_data *data, t_table_data *cmd, char **envp)
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
	final_cmd_execute(data, cmd, envp);
}

static bool	pipe_on_table(t_data *data)
{
	int	i;

	i = 0;
	while (data->table[i])
	{
		if (data->table[i]->type == PIPE)
			return (true);
		i++;
	}
	return (false);
}

/*
 *
 * 	· if cmd = exit
 * 		· do exit stuff
 * 	· init envp
 * 	· start process (pid = fork)
 * 	· if pid = -1
 * 		· error
 * 	· else
 * 		· child_process()
 * 	· free and close stuff
 */
static void	cmd_process(t_data *data, t_table_data *cmd)
{
	char	*envp[2];

	if (!ft_strcmp(cmd->name, "exit") && pipe_on_table(data) == false)
	{
		ft_exit(cmd->args, data);
		return ;
	}
	envp[0] = ft_strdup("TERM=xterm");
	envp[1] = NULL;
	cmd->pid = fork();
	if (cmd->pid == -1)
	{
		perror("command process error");
		data->error = true;
		exit(EXIT_FAILURE);
	}
	else if (cmd->pid == 0)
		child_process(data, cmd, envp);
	else
	{
		waitpid(cmd->pid, &data->process_status, 0);
		if (cmd->in_fd)
			close(cmd->in_fd);
		if (cmd->out_fd)
			close(cmd->out_fd);
		free(envp[0]);
		// TODO : data->env = tempfile
	}
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
		cmd_process(data, cmd);
	}
	else
	{
		data->error = true;
		ft_error(3, cmd->name);
		data->process_status = 127;
	}
	free(cmd->path);
}
