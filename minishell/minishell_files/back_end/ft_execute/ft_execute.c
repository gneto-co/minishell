/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:23:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 16:06:47 by gneto-co         ###   ########.fr       */
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
		if (data->table[i]->type == CMD)
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
	// ft_printf("1 - process_status: %d\n", data->process_status);
	while (data->table[i])
	{
		if (data->table[i]->type == CMD)
		{
			if (data->table[i]->pid)
				waitpid(data->table[i]->pid, &status, 0);
			// ft_printf("wifsignaled: %d\n", WIFSIGNALED(status));
			if (WIFEXITED(status))
				data->process_status = WEXITSTATUS(status);
			// else if (WIFSIGNALED(status))
			// {
			// 	data->process_status = 128 + WTERMSIG(status);
			// 	ft_printf("CHECK\n");
			// }
		}
		if (data->table[i]->type == PIPE)
		{
			close(data->table[i]->pipe_fd[0]);
			close(data->table[i]->pipe_fd[1]);
		}
		i++;
	}
	// ft_printf("2 - process_status: %d\n", data->process_status);
}

/* reset std in/out */
static void	reset_loop(t_data *data)
{
	data->in_fd = 0;
	data->out_fd = 0;
	unlink(LESSLESS_TEMP_FILE);
}

/* receive data and execute commands from commands table */
int	ft_execute(t_data *data)
{
	// ft_print_table(data->table);
	if (data->error == false)
	{
		first_loop(data);
		second_loop(data);
		wait_pid_loop(data);
		reset_loop(data);
	}
	return (0);
}
