/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 15:53:52 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	data_init(t_data *data, char **env)
{
	data->env = env;
	data->error = false;
	data->infile_error = false;
	data->table = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->exit = false;
	data->exit_code = 0;

}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, env);
	ft_readline_loop(&data);
	exit(data.process_status);
}
