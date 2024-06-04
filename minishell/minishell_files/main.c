/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/04 22:45:49 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	data_init(t_data *data, char **env)
{
	data->env = ft_array_dup(env);
	data->error = false;
	data->infile_error = false;
	data->table = NULL;
	data->in_fd = 0;
	data->out_fd = 0;
	data->exit = false;
	data->exit_code = 0;
	init_or_exit_update_env(&(data->env), "init");
}

static void	data_free(t_data *data)
{
	ft_free_array(data->env);
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, env);
	ft_readline_loop(&data);
	data_free(&data);
	exit(data.process_status); //FIXME "exit 3" não funciona
}

/* int	main(void)
{
	char	*array[] = {"hola", "mundo", "como", "estas", NULL};
	char	**array2;

	array2 = ft_array_dup(array);
	ft_print_array(array2);
	free_array(&array2);
}
  */
