/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_flags_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:12:43 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 11:32:50 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	new_line_initialize_data(t_table_data *new_line)
{
	new_line->name = NULL;
	new_line->flags = malloc(sizeof(char *));
	new_line->flags[0] = NULL;
	new_line->flags_amount = 0;
	new_line->args = malloc(sizeof(char *));
	new_line->args[0] = NULL;
	new_line->args_amount = 0;
}

/*
 * 	function : will transform tokens into a command
 *
 * 	· first token : name
 * 	· next tokens - started : flags
 * 	· next tokens : args
 */
static void	cmd_manager(t_table_data *new_line, char **array, int *ii)
{
	int	i;

	i = *ii;
	if (new_line->type == CMD)
		new_line->name = array[i - 1];
	while (get_line_type(array, i) == CMD)
	{
		if (ft_strncmp(array[i], "-", 1) != 0)
			break ;
		new_line->flags = split_str(new_line->flags, &new_line->flags_amount,
				ft_strdup(array[i]));
		i++;
	}
	while (get_line_type(array, i) == CMD)
	{
		new_line->args = split_str(new_line->args, &new_line->args_amount,
				ft_strdup(array[i]));
		i++;
	}
	*ii = i;
}

/*
 * 	function : will transform tokens into a redirection
 *
 * 	· if next token isn't a normal string : error
 * 	· if it is put it as file name
 */
static void	redirection_manager(t_data *data, t_table_data *new_line,
		char **array, int *ii)
{
	int		i;
	char	*type;
	int		t;

	t = new_line->type;
	i = *ii;
	if (get_line_type(array, i) != 1)
	{
		if (t == LESS)
			type = ft_strdup("<");
		if (t == LESSLESS)
			type = ft_strdup("<<");
		if (t == GREAT)
			type = ft_strdup(">");
		if (t == GREATGREAT)
			type = ft_strdup(">>");
		data->error = true;
		ft_error(2, type);
		return ;
	}
	new_line->name = array[i++];
	*ii = i;
}

/*
 * 	function : will see tokens and put correspondent name,
		args and flags on new_line
 *
 * 	if <, <<, > or >> : get the file name
 * 	if | : do nothing
 * 	if cmd : look for name, flags and args
 *
 * 	· initialize vars
 * 	· if is a redirection : redirection_manager
 * 	· if is a command : cmd_manager
 */
t_table_data	*get_name_flags_args(t_table_data *new_line, char **array,
		int *ii, t_data *data)
{
	int	i;
	int	t;

	t = new_line->type;
	i = *ii + 1;
	new_line_initialize_data(new_line);
	if (t == LESS || t == LESSLESS || t == GREAT || t == GREATGREAT)
		redirection_manager(data, new_line, array, &i);
	else if (t == CMD)
	{
		cmd_manager(new_line, array, &i);
		if (data->error == true)
			return (new_line);
	}
	*ii = i;
	return (new_line);
}
