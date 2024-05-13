/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:28 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void data_init(t_data *data)
{
	data->error = false;
}


static char	*input_text(void)
{
	char	*folder_name;
	char	*input_str;

	folder_name = ft_get_folder_name();
	input_str = ft_multi_strjoin("\n"
									"╭─┤ %s ├─\n"
									"│\n"
									"╰─────────► ",
									folder_name);
	free(folder_name);
	return (input_str);
}

static void	input_use(char *input, t_data *data, char **env)
{
	char	**array;
	// int		i;

	// i = 0;
	data_init(data);
	array = ft_token_split(input, data, env);
	if (data->error == false)
	{
		// ft_putstr("\n\n");
		// while (array[i])
		// 	ft_printf("%s\n", array[i++], "\x1b[7m%\x1b[0m");
		// ft_printf("%s\n\n", array[i++], "\x1b[7m%\x1b[0m");

		data->exit_code = ft_execute(array);
	}
	ft_free_array(array);
}

// ft_get_user_input()
int	main(int ac, char **av, char **env)
{
	char	*input;
	char	*input_str;
	t_data	data;

	(void)ac;
	(void)av;
	// initialize
	using_history();
	ft_data()->exit = false;
	// readline loop
	while (true)
	{
		// read a line from stdin
		input_str = input_text();
		input = readline(input_str);
		// if the input is null that means the user press Ctrl+D (EOF)
		if (input == NULL)
		{
			ft_printf("\n");
			break ;
		}
		// if theres something on input
		// add a line to history and use input
		if (input[0])
		{
			add_history(input);
			input_use(input, &data, env);
		}
		// free input
		free(input);
		if (ft_data()->exit)
			break ;
	}
	// Limpa o histórico
	clear_history();
	exit(data.exit_code);
}
