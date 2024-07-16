/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:25:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/07/16 13:34:50 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* static char	*get_input(void)
{
	char	*input;
	// static int n = 0;

	input = NULL;
	// printf("n = %d\t", ++n); // MARK n=
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
	input = readline(PROMPT_STR);
	// signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_DFL);
	return (input);
} */

static char	*get_input(void)
{
	char	*input;
	// static int n = 0;

	input = NULL;
	// printf("n = %d\t", ++n); // MARK n=
	signals(def);
	input = readline(PROMPT_STR);
	// signal(SIGINT, SIG_IGN);
	return (input);
}

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
	data->signal_mod = 0;
	data->input_array = ft_token_split(data->input_str, data);
	if (data->error == false)
	{
		data->signal_mod = 1;
		data->raw_input_array = ft_token_split(data->input_str, data);
		data->signal_mod = 2;
		data->signal_input_array = ft_token_split(data->input_str, data);
		data->table = create_cmd_table(data->input_array, data);
		if (data->error == false)
			ft_execute(data);
		ft_free_table(data->table);
		free(data->table);
		ft_free_array(data->raw_input_array);
		ft_free_array(data->signal_input_array);
	}
	data->error = false;
	ft_free_array(data->input_array);
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

	last_input = (using_history(), NULL);
	while (!data->exit)
	{
		input = get_input();
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
