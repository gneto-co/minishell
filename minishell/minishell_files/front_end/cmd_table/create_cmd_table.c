/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cmd_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 13:20:59 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 16:42:02 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* return the line type */
int	get_line_type(char **array, int i)
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

/*
 * 	function : see on array tokens and get new line
 *
 * 	· error manager, initialize / alloc vars
 * 	· get new line type
 * 	· get name / args
 */
static t_table_data	*get_new_line(char **array, int *ii, t_data *data)
{
	int				i;
	t_table_data	*new_line;

	i = *ii;
	if (!array || !array[i])
		return (NULL);
	new_line = malloc(sizeof(t_table_data));
	new_line->type = get_line_type(array, i);
	new_line = get_name_args(new_line, array, &i, data);
	*ii = i;
	return (new_line);
}

/*
 * 	function : increase (realloc) table space, put new_line in the table
 *
 * 	· error manager, initialize vars
 * 	· realloc table with +1 line
 * 	· if no errors
 * 		· put new_line on table's new space
 * 		· put NULL on last table space
 */
static t_table_data	**split_table(t_table_data **table, int *table_size,
		t_table_data *new_line)
{
	t_table_data	**temp;

	if (!new_line)
		return (table);
	temp = NULL;
	temp = ft_realloc(table, sizeof(t_table_data *) * (*table_size + 1),
			sizeof(t_table_data *) * (*table_size + 2));
	if (temp == NULL)
		return (ft_error(0, NULL), NULL);
	else
		table = temp;
	(*table_size)++;
	table[*table_size - 1] = new_line;
	table[*table_size] = NULL;
	return (table);
}

/*
 * 	function : transform tokens into a command table
 *
 * 	· initialize data
 * 	· read all tokens loop
 * 		· get_new_line (new line is a command/operator and is args)
 * 		· if !new_line : break
 * 		· else : put new_line on table
 * 	· return table
 */
t_table_data	**create_cmd_table(char **array, t_data *data)
{
	int				i;
	int				table_size;
	t_table_data	**table;
	t_table_data	*new_line;

	i = 0;
	table_size = 0;
	table = malloc(sizeof(t_table_data *));
	table[0] = NULL;
	while (1)
	{
		new_line = get_new_line(array, &i, data);
		if (!new_line)
			break ;
		else
		{
			table = split_table(table, &table_size, new_line);
			if (!table)
				data->error = true;
			new_line = NULL;
		}
		if (data->error == true)
			break ;
	}
	return (table);
}
