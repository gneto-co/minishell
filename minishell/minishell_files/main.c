/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 13:04:02 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**create_env(void)
{
	char	**array_env;
	char	cwd[1024];

	array_env = malloc(sizeof(char *) * 5);
	if (getcwd(cwd, sizeof(cwd)))
	{
		array_env[0] = ft_strjoin("PWD=", cwd);
		array_env[1] = ft_strjoin("OLDPWD=", cwd);
		array_env[2] = ft_strdup("SHLVL=0");
		array_env[3] = ft_strdup("_=/usr/bin/env");
		array_env[4] = NULL;
	}
	return (array_env);
}

static void	env_init(t_data *data, char **env)
{
	char **array_env;

	array_env = NULL;
	if (access(ENV_FILE, F_OK) != -1)
		data->env = ft_file_to_array(ENV_FILE);
	else
	{
		if (!*env)
			array_env = create_env();
		else
			array_env = ft_array_dup(env);
		data->env = ft_array_dup(array_env);
		free_array(&array_env);
	}
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
	data->input_array = NULL;
	data->signal_mod = 0;
}

static void	data_free(t_data *data)
{
	// init_or_exit_update_env(&(data->env), "exit"); // lvl-- MARK
	unlink(ENV_FILE); // FIXME
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
