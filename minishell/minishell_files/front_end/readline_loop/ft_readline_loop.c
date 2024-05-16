/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:25:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 14:59:03 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* allocate and return a str with the prompt */
static char	*get_prompt_text(void)
{
	char	*folder_name;
	char	*input_str;

	folder_name = ft_get_folder_name();
	input_str = ft_multi_strjoin("\n"
									"╭─┤ /%s ├─\n"
									"│\n"
									"╰─────────► ",
									folder_name);
	free(folder_name);
	return (input_str);
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
static void	input_use(char *input, t_data *data)
{
	char	**input_array;

	input_array = ft_token_split(input, data);
	if (data->error == false)
	{
		data->table = create_cmd_table(input_array, data);
		ft_execute(data);
	}
	data->error = false;
	ft_free_array(input_array);
	ft_free_table(data->table);
	free(data->table);
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
 *	· start a readline() loop with functional history
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
	char	*prompt_str;

	last_input = NULL;
	using_history();
	while (1)
	{
		prompt_str = get_prompt_text();
		input = readline(prompt_str);
		free(prompt_str);
		if (!input)
		{
			free(input);
			ft_printf("\n");
			break ;
		}
		if (input[0])
			input_use(input, data);
		history_manager(input, &last_input);
		free(input);
	}
	free(last_input);
	clear_history();
}
