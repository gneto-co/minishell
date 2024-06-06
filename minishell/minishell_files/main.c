/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/06 14:29:12 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	env_init(t_data *data, char **env)
{
	if (access(ENV_FILE, F_OK) != -1)
		data->env = ft_file_to_array(ENV_FILE);
	else
		data->env = ft_array_dup(env);
	init_or_exit_update_env(&(data->env), "init");
	ft_array_to_file(data->env, ENV_FILE);
}

static void	data_init(t_data *data)
{
	data->error = false;
	data->infile_error = false;
	data->process_status = 0;
	data->table = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->exit = false;
	data->output_string = NULL;
}

static void	data_free(t_data *data)
{
	// init_or_exit_update_env(&(data->env), "exit"); // lvl-- // MARK
	unlink(ENV_FILE);
	ft_free_array(data->env);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	env_init(&data, env);
	data_init(&data);
	ft_readline_loop(&data);
	data_free(&data);
	exit(data.process_status);
}
