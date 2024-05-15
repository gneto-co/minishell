/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline_loop.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 14:25:48 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 14:15:55 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// that function will return a str with the prompt
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

// that is the function where the input will be used
static void	input_use(char *input, t_data *data, char **env)
{
	char	**array;
	int		i;

	//
	// initialize vars
	//
	(void) i;
	i = 0;
	//
	// transform input into tokens
	//
	array = ft_token_split(input, data, env);
	//
	// if there is no error on t_data: use input
	//
	if (data->error == false)
	{
		//
		// print array with args
		//
		/* 
		ft_putstr("\n\n");
		while (array[i])
		    ft_printf("%s%s\n", array[i++], "\x1b[7m%\x1b[0m");
		ft_printf("%s%s\n\n", array[i++], "\x1b[7m%\x1b[0m"); 
		 */
		//
		// execute the commands
		//
		ft_execute(array, data, env);
	}
	if (data->error == true)
		data->error = false;
	//
	// free stuff
	//
	ft_free_array(array);
	//
	// end
	//
}

// that is the function that will get stdin and then use it
// readline loop
void	ft_readline_loop(t_data *data, char **env)
{
	char	*input;
	char	*last_input;
	char	*prompt_str;

	//
	// initialize vars
	//
	last_input = NULL;
	using_history();
	//
	// readline loop
	//
	while (1)
	{
		//
		// read a line from stdin
		//
		prompt_str = get_prompt_text();
		input = readline(prompt_str);
		//
		// if the input is null that means the user press Ctrl+D (EOF)
		//
		if (input == NULL)
		{
			free(input);
			free(prompt_str);
			ft_printf("\n");
			break ;
		}
		//
		// if theres something on input: use input
		//
		if (input[0])
			input_use(input, data, env);
		//
		// if theres something on input, if input != last_input: add_history
		//
		if (input[0] && ft_strcmp(input, last_input))
		{
			add_history(input);
			if (last_input)
				free(last_input);
			last_input = ft_strdup(input);
		}
		//
		// free input
		//
		free(input);
		free(prompt_str);
	}
	//
	// free stuff
	//
	free(last_input);
	clear_history();
	//
	// end
	//
}
