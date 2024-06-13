/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:12:43 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/13 20:34:00 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	new_line_initialize_data(t_table_data *new_line)
{
	new_line->name = NULL;
	new_line->args = malloc(sizeof(char *));
	new_line->args[0] = NULL;
	new_line->args_amount = 0;
	new_line->in_fd = 0;
	new_line->out_fd = 0;
	new_line->path = NULL;
	new_line->pid = 0;
}

static void	set_cmd_arg(t_data *data, t_table_data *new_line, char **array,
		int i)
{
	char	*temp_str;
	char	**temp_split;
	int		j;
	char	quote;
	int		extra;

	extra = 0;
	quote = array[i][0];
	if (quote == '\'' || quote == '\"')
		extra++;
	// ft_printf("array[i] = %s\n", array[i]); //MARK
	if (ft_strncmp(array[i] + extra, "$", 1) == 0 && (quote != '\''))
	{
		// ft_printf("array[i] = %s\n", array[i] + extra + 1); //MARK

		/** //FIXME
		 * erra bug, command: echo $US result: R=yadereve
		 * temp_str = ft_get_system_var(array[i] + extra + 1, data->env);
		*/

		temp_str = ft_getenv(array[i] + extra + 1, data->env);
		temp_split = ft_split(temp_str, ' ');
		j = 0;
		while (temp_split[j])
		{
			new_line->args = split_str(new_line->args, &new_line->args_amount,
					ft_strdup(temp_split[j]));
			j++;
		}
		ft_free_array(temp_split);
		free(temp_str);
	}
	else
	{
		new_line->args = split_str(new_line->args, &new_line->args_amount,
				ft_strdup(array[i] + extra));
	}
}

static char	*get_name(char *str, t_data *data, int t)
{
	char	*new_str;
	char	**temp_array;
	char	quote;

	quote = str[0];
	if (quote == '\'' || quote == '\"')
		str++;
	if ((ft_strncmp(str, "$", 1) == 0) && (t == CMD) && (quote != '\''))
	{
		str++;
		new_str = ft_get_system_var(str, data->env);
		if (!new_str || !ft_strchr(new_str, ' '))
		{
			return (new_str);
		}
		temp_array = ft_split(new_str, ' ');
		new_str = ft_strdup(temp_array[0]);
		ft_free_array(temp_array);
		return (new_str);
	}
	else if ((ft_strncmp(str, "$", 1) == 0) && (t != LESSLESS)
		&& (quote != '\''))
	{
		str++;
		new_str = ft_get_system_var(str, data->env);
		if (!ft_strchr(new_str, ' '))
			return (new_str);
		data->error = true;
		ft_error(5, --str);
		return (NULL);
	}
	else
		return (ft_strdup(str));
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

	i = *ii;
	i--;
	if (new_line->type == CMD)
		new_line->name = get_name(array[i], data, CMD);
	// new_line->args = split_str(new_line->args, &new_line->args_amount,
	// 		ft_strdup(new_line->name));
	// 	set_cmd_arg(data, new_line, array, i);
	while (get_line_type(array, i) == CMD)
	{
		// FIXME cmd: echo $43, res: \n
		// ft_print_array_tester(new_line->args); // MARK
		set_cmd_arg(data, new_line, array, i);
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
		data->error = true;
		ft_error(2, type);
		free(type);
		return ;
	}
	new_line->name = get_name(array[i++], data, t);
	*ii = i;
}

/*
 * 	function : will see tokens and put correspondent name and
 * 	args on new_line
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
	new_line_initialize_data(new_line);
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
