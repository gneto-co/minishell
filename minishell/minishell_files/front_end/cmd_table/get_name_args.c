/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:12:43 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 12:40:15 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*ft_corr(t_data *data, char *str, int i)
{
	char	*temp_str;

	temp_str = NULL;
	if (str[0] == '$' && ft_isdigit(str[1]))
	{
		temp_str = ft_substr(str, 2, ft_strlen(str));
	}
	else
	{
		if (data->signal_input_array[i][0] == '\'')
			temp_str = ft_strdup(data->raw_input_array[i]);
		else
			temp_str = ft_strdup(data->input_array[i]);
	}
	return (temp_str);
}

static void	exception_manager(t_data *data, t_table_data *new_line,
		char **array, int *ii)
{
	int		i;
	char	*new_str;

	i = *ii;
	new_str = NULL;
	while (get_line_type(array, i) == CMD)
	{
		new_str = ft_strdup(data->raw_input_array[i]);
		new_str = ft_corr(data, (new_str), i);
		new_line->args = split_str(new_line->args, &new_line->args_amount,
				new_str);
		i++;
	}
	*ii = i;
}

/*
 * 	function : will transform tokens into a command
 *
 * 	· first token : name
 * 	· next tokens : args
 */
static void	cmd_manager(t_data *data, t_table_data *new_line, char **array,
		int *ii)
{
	int	i;

	(void)data;
	i = *ii;
	if (new_line->type == CMD)
		new_line->name = ft_strdup(array[i - 1]);
	new_line->args = split_str(new_line->args, &new_line->args_amount,
			ft_strdup(new_line->name));
	if (ft_strcmp(new_line->name, "echo") == 0)
		exception_manager(data, new_line, array, &i);
	else
	{
		while (get_line_type(array, i) == CMD)
		{
			new_line->args = split_str(new_line->args, &new_line->args_amount,
					ft_strdup(array[i]));
			i++;
		}
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
	type = NULL;
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
		data->error = (free(type), ft_error(2, type), true);
		return ;
	}
	if (t == LESSLESS)
		new_line->name = ft_strdup(data->raw_input_array[i++]);
	else
		new_line->name = ft_strdup(array[i++]);
	*ii = i;
}

/*
 * 	function : will see tokens and put correspondent name,
		args on new_line
 *
 * 	if <, <<, > or >> : get the file name
 * 	if | : do nothing
 * 	if cmd : look for name and args
 *
 * 	· initialize vars
 * 	· if is a redirection : redirection_manager
 * 	· if is a command : cmd_manager
 */
t_table_data	*get_name_args(t_table_data *new_line, char **array, int *ii,
		t_data *data)
{
	int	i;
	int	t;

	t = new_line->type;
	i = *ii + 1;
	new_line->name = NULL;
	new_line->args = malloc(sizeof(char *));
	new_line->args[0] = NULL;
	new_line->args_amount = 0;
	new_line->in_fd = 0;
	new_line->out_fd = 0;
	new_line->path = NULL;
	new_line->pid = 0;
	if (t == LESS || t == LESSLESS || t == GREAT || t == GREATGREAT)
		redirection_manager(data, new_line, array, &i);
	else if (t == CMD)
	{
		cmd_manager(data, new_line, array, &i);
		if (data->error == true)
			return (new_line);
	}
	*ii = i;
	return (new_line);
}
