/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:33:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/25 12:25:04 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// that funtion initializate all vars if t_data
static void	data_init(t_data *data, char **env)
{
	data->error = false;
	data->exit = false;
	data->exit_code = 0;
	data->env = env;

}

// that function will return a str with the prompt
static char	*get_prompt_text(void)
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

// that is the function where the input will be used
static void	input_use(char *input, t_data *data, char **env)
{
	char	**array;
	// int		i;

	//
	// initialize vars
	//
	// i = 0;
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
		// by now, it is only printing the args
		//
		/* ft_putstr("\n\n");
		while (array[i])
			ft_printf("%s%s\n", array[i++], "\x1b[7m%\x1b[0m");
		ft_printf("%s%s\n\n", array[i++], "\x1b[7m%\x1b[0m");
		*/
		ft_execute(array, data); //NOTE
	}
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
static void	readline_loop(t_data *data, char **env)
{
	char	*input;
	// char	*input_str;
	// t_data	data;

	// initialize
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
	while (!data->exit)
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
	}
	//
	// free stuff
	//
	free(last_input);
	free(prompt_str);
	clear_history();
	//
	// end
	//
}

// FIXME run .minishell, SHLVL= (+1); exit, SHLVL= (-1)
// ft_get_user_input()
int	main(int ac, char **av, char **env)
{
	t_data	data;

	(void)ac;
	(void)av;
	data_init(&data, env);
	readline_loop(&data, env);
	exit(data.exit_code);
}
