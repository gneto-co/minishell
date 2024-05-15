/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:20:59 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 14:53:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// return the line type
static int	get_line_type(char **array, int i)
{
	if (!array[i])
		return (0);
	else if (!ft_strcmp(array[i], "|"))
		return (PIPE);
	else if (!ft_strcmp(array[i], "<"))
		return (LESS);
	else if (!ft_strcmp(array[i], ">"))
		return (GREAT);
	else if (!ft_strcmp(array[i], "<<"))
		return (LESSLESS);
	else if (!ft_strcmp(array[i], ">>"))
		return (GREATGREAT);
	else
		return (CMD);
}

static t_table_data	*get_flags_args(t_table_data *new_line, char **array,
		int *ii, t_data *data)
{
	int	i;
	int	t;
	char *type;

	//
	// declarations
	//
	i = *ii + 1;
	t = new_line->type;
	new_line->name = NULL;
	new_line->flags = malloc(sizeof(char *));
	new_line->flags[0] = NULL;
	new_line->flags_amount = 0;
	new_line->args = malloc(sizeof(char *));
	new_line->args[0] = NULL;
	new_line->args_amount = 0;
	//
	// if <, <<, > or >> : get the file name
	// if | : do nothing
	// if cmd : look for name, flags and args
	//
	if (t == LESS || t == LESSLESS || t == GREAT || t == GREATGREAT)
	{
		//
		// if array[i] is not a regular str: error
		//
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
			return (ft_error(2, type), new_line);
		}
		new_line->name = array[i++];
	}
	else if (t == CMD)
	{
		//
		// get name
		//
		if (new_line->type == CMD)
			new_line->name = array[i - 1];
		//
		// get all the flags
		//
		while (get_line_type(array, i) == CMD)
		{
			if (ft_strncmp(array[i], "-", 1) != 0)
				break ;
			new_line->flags = split_str(new_line->flags,
					&new_line->flags_amount, ft_strdup(array[i]));
			i++;
		}
		//
		// get all the args
		//
		while (get_line_type(array, i) == CMD)
		{
			new_line->args = split_str(new_line->args, &new_line->args_amount,
					ft_strdup(array[i]));
			i++;
		}
	}
	//
	// end
	//
	*ii = i;
	return (new_line);
}

static t_table_data	*get_new_line(char **array, int *ii, t_data *data)
{
	int				i;
	t_table_data	*new_line;

	//
	// error management
	// initialize/allocate data
	//
	i = *ii;
	if (!array || !array[i])
		return (NULL);
	new_line = malloc(sizeof(t_table_data));
	//
	// get line type
	//
	new_line->type = get_line_type(array, i);
	//
	// get flags / args
	//
	new_line = get_flags_args(new_line, array, &i, data);
	//
	// end
	//
	*ii = i;
	return (new_line);
}

static t_table_data	**split_table(t_table_data **table, int *table_size,
		t_table_data *new_line)
{
	t_table_data	**temp;

	//
	// error management
	//
	if (!new_line)
		return (table);
	//
	// initialize/allocate data
	//
	temp = NULL;
	//
	// realloc table with a new greater
	//
	temp = ft_realloc(table, sizeof(t_table_data *) * (*table_size + 1),
			sizeof(t_table_data *) * (*table_size + 2));
	if (temp == NULL)
		return (ft_error(0, NULL), NULL);
	else
		table = temp;
	//
	// increase the table size
	// put new_line on table
	// put NULL on table end
	//
	(*table_size)++;
	table[*table_size - 1] = new_line;
	table[*table_size] = NULL;
	//
	// end
	//
	return (table);
}

t_table_data	**create_cmd_table(char **array, t_data *data)
{
	int				i;
	int				table_size;
	t_table_data	**table;
	t_table_data	*new_line;

	//
	// initialize data
	//
	i = 0;
	table_size = 0;
	table = malloc(sizeof(t_table_data *));
	table[0] = NULL;
	//
	// get_new_line loop
	//
	while (1)
	{
		//
		// get new line
		//
		new_line = get_new_line(array, &i, data);
		//
		// if there is no new_line or is an error: stop
		//
		if (!new_line)
			break ;
		//
		// else: put new line on table
		//
		else
		{
			table = split_table(table, &table_size, new_line);
			if (!table)
				data->error = true;
			new_line = NULL;
		}
		//
		// if finds a error: stop
		//
		if (data->error == true)
			break;
	}
	return (table);
}
