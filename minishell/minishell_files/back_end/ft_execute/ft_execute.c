/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:23:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/25 16:41:12 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* first loop : prepare pipes and redirection */
static void	first_loop(t_data *data)
{
	int	i;

	i = 0;
	while (data->table[i])
	{
		if (data->table[i]->type == PIPE)
			ex_pipe(data, i);
		else if (data->table[i]->type == LESS)
			ex_less(data, i);
		else if (data->table[i]->type == LESSLESS)
			ex_lessless(data, i);
		else if (data->table[i]->type == GREAT)
			ex_great(data, i);
		else if (data->table[i]->type == GREATGREAT)
			ex_greatgreat(data, i);
		i++;
	}
}

/* second loop : execute commands */
static void	second_loop(t_data *data)
{
	int	i;

	i = 0;
	while (data->table[i])
	{
		if (data->table[i]->type == CMD /* && data->error != true */)
			// NOTE !pode estragar!
			ex_cmd(data, i);
		i++;
	}
}

/* waitpid loop : wait for all processes and close pipes */
static void	wait_pid_loop(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (data->table[i])
	{
		status = 0;
		if (data->table[i]->type == CMD)
		{
			if (data->table[i]->pid)
			{
				// ft_printf("\n cmd name -> %s\n", data->table[i]->name); // MARK print cmd name on waitpid
				waitpid(data->table[i]->pid, &status, 0);
			}
			if (WIFEXITED(status) && !data->process_status)
				data->process_status = WEXITSTATUS(status);
		}
		// MARK
		// ft_printf("%s\n", data->table[i]);
		if (data->table[i]->type == PIPE)
		{
			if (data->table[i]->pipe_fd[0] && data->table[i]->pipe_fd[1])
			{
				close(data->table[i]->pipe_fd[0]);
				close(data->table[i]->pipe_fd[1]);
			}
		}
		i++;
	}
}

/* reset std in/out */
static void	reset_loop(t_data *data)
{
	if (data->in_fd)
		close(data->in_fd);
	if (data->out_fd)
		close(data->out_fd);
	data->in_fd = 0;
	data->out_fd = 0;
	unlink(LESSLESS_TEMP_FILE);
	ft_array_to_file(data->env, ENV_FILE);
}

/* receive data and execute commands from commands table */
int	ft_execute(t_data *data)
{
	if (data->error == false)
	{
		first_loop(data);
		second_loop(data);
		wait_pid_loop(data);
		reset_loop(data);
	}
	return (0);
}
