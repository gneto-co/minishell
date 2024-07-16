/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parent_process_basic_cmd.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:22 by gneto-co          #+#    #+#             */
/*   Updated: 2024/07/16 13:42:48 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

static void	final_cmd_execute(t_data *data, t_table_data *cmd, char **envp)
{
	signal(SIGINT, SIG_DFL);
	if ((!data->table[cmd->pos + 1] || (!data->table[cmd->pos + 2]
				&& data->table[cmd->pos + 1]->type != PIPE)) && have_pipes(data)
		&& cmd->args_amount == 1)
		exit(0);
	if (ft_strcmp(cmd->name, "") == 0)
		exit(0);
	data->process_status = execve(cmd->path, cmd->args, envp);
	perror("command process error");
	data->error = true;
}

/*
 *
 * 	· configure pipe / redirection
 * 	· execute cmd
 * 	· error management
 */
static void	child_process(t_data *data, t_table_data *cmd, char **envp)
{
	signals(child);
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
void	parent_process_basic_cmd(t_data *data, t_table_data *cmd)
{
	char	*envp[2];

	envp[0] = ft_strdup("TERM=xterm");
	envp[1] = NULL;
	cmd->pid = fork();
	signals(ignor);
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
		if (cmd->in_fd)
			close(cmd->in_fd);
		if (cmd->out_fd)
			close(cmd->out_fd);
		free(envp[0]);
	}
}
