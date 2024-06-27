/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:33:15 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/27 11:51:01 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	ft_print_array(char **array)
// {
// 	int	i;

// 	i = 0;
// 	while (array[i])
// 		printf("array: %s\n", array[i++]);
// }

/**
 * Frees the memory allocated for a 3-dimensional array.
 */
void	free_array(char ***array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!(*array))
		return ;
	while ((*array)[len])
		len++;
	while (i < len)
	{
		free((*array)[i]);
		i++;
	}
	free((*array));
}

/**
 * Checks if a given string is a valid identifier.
 */
bool	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) || str[0] == '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (false);
		i++;
	}
	return (true);
}

/**
 * Creates a new environment variable with the given value.
 */
char	**ft_create_env(char *new_var)
{
	char	**new_env;

	new_env = malloc(2 * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[0] = ft_strdup(new_var);
	if (new_env[0] == NULL)
		return (NULL);
	new_env[1] = NULL;
	return (new_env);
}

/**
 * This function takes a pointer to a pointer to the environment variable array
 * and a new variable as input. It adds the new variable to the array,
 * reallocating memory if necessary. If the array is empty, it creates a new
 * array with the new variable. If the array is not empty, it creates a new a
 * array with the new variable appended to the existing array.
 * The old array is freed and the pointer is updated to point to the new array.
 */
void	add_new_arg(char ***env, char *new_var)
{
	int		len;
	char	**new_env;
	int		i;

	if (!(*env))
		*env = ft_create_env(new_var);
	else
	{
		i = 0;
		len = ft_arraylen(*env);
		new_env = malloc((len + 2) * sizeof(char *));
		if (!new_env)
			return ;
		while ((*env)[i])
		{
			new_env[i] = ft_strdup((*env)[i]);
			i++;
		}
		new_env[i] = ft_strdup(new_var);
		new_env[i + 1] = NULL;
		free_array(env);
		*env = new_env;
	}
}
