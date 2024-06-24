/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:25:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/24 22:33:11 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *	· use the raw input:
 *		· divide input into tokens (input_array)
 *		(if no error)
 *		· create a command table from tokens
 *		· execute the command table
 *	· reset error
 *	· free table and input_array
 */
static void	input_use(t_data *data)
{
	ft_printf("%s\n", data->input_str); // MARK print data str
	//
	data->ignore_env = true;
	data->raw_input_array = ft_token_split(data->input_str, data);
	ft_print_array_tester(data->raw_input_array); // MARK print raw data array
	//
	data->ignore_env = false;
	data->input_array = ft_token_split(data->input_str, data);
	ft_print_array_tester(data->input_array); // MARK print data array
	//
	if (data->error == false)
	{
		data->table = create_cmd_table(data->input_array, data);
		ft_print_table(data->table); // MARK print data table
		if (data->error == false)
			ft_execute(data);
		ft_free_table(data->table);
		free(data->table);
	}
	data->error = false;
	ft_free_array(data->input_array);
	ft_free_array(data->raw_input_array);
}

/*
 *	· if something on input and input != last input
 *		· add input to history
 *		· update last_input
 */
static void	history_manager(char *input, char **last_input)
{
	if (input[0] && ft_strcmp(input, *last_input))
	{
		add_history(input);
		if (*last_input)
			free(*last_input);
		*last_input = ft_strdup(input);
	}
}

/*
 *
 * 	· configure signal handlers
 * 	· start a readline() loop with functional history
 *		· get prompt, get input, free prompt
 *		· if !input (Ctr+D)
 *			· free() input, prompt
 *			· print a new line
 *			· break loop
 *		· if something on input
 *			· use it
 *		· history_manager()
 *	· free last_input and history
 */
void	ft_readline_loop(t_data *data)
{
	char	*input;
	char	*last_input;

	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	last_input = (using_history(), NULL);
	while (!data->exit)
	{
		input = readline(PROMPT_STR);
		if (!input)
		{
			free(input);
			ft_printf("exit\n");
			break ;
		}
		if (input[0])
		{
			data->input_str = input;
			input_use(data);
		}
		history_manager(input, &last_input);
		free(input);
	}
	free(last_input);
	clear_history();
}
