/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:47 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/25 12:10:33 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * This function removes the element at the specified index from the array and
 * updates the array accordingly. It dynamically allocates a new array with
 * enough space to hold the remaining elements and copies them over. The old
 * array is then freed.
 */
void	ft_array_n_delone(char ***array, int index)
{
	int		i;
	int		j;
	int		len;
	char	**new_array;

	if (!(*array))
		return ;
	i = 0;
	j = 0;
	len = ft_arraylen((*array));
	new_array = malloc(len * sizeof(char *));
	if (!new_array)
		return ;
	while ((*array)[i])
	{
		if (i != index)
		{
			new_array[j] = ft_strdup((*array)[i]);
			j++;
		}
		i++;
	}
	new_array[j] = NULL;
	ft_free_array((*array));
	(*array) = new_array;
}

/**
 * This function takes an array of arguments and a pointer to a data structure.
 * It iterates through the arguments and checks if each argument contains an
 * equal sign. If an argument contains an equal sign, it prints an error
 * message and sets the exit code to 1. If an argument does not contain an
 * equal sign, it searches for the variable in the environment array.
 * If the variable is found, it removes it from the environment array.
 */
void	ft_unset(char **args, t_data *data)
{
	int	i;
	int	index_env;

	i = 1;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			ft_putstr_fd("minishell: unset:", STDERR_FILENO);
			ft_putstr_fd(args[i], STDERR_FILENO);
			ft_putendl_fd(": invalid parameter name", STDERR_FILENO);
			data->process_status = 1;
		}
		else
		{
			index_env = find_var(data->env, args[i]);
			if (index_env >= 0)
				ft_array_n_delone(&(data->env), index_env);
		}
		i++;
	}
}
