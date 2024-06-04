/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:28:28 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/04 16:54:39 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Updates the value of a string pointer with a new variable.
 * This function takes a string pointer and a new variable as input.
 * It updates the value of the string pointer by duplicating the new variable.
 * If the string pointer was previously pointing to a string, it frees the
 * memory allocated for that string before duplicating the new variable.
 */
void	update_env_str(char **str, char *new_var)
{
	// if (*str)
	// 	free(*str); //LEAK maybe, error malloc()
	*str = ft_strdup(new_var);
}

/**
 * Retrieves the environment variable from a given string.
 * This function searches for the first occurrence of the '=' character in the
 * input string and returns a substring of the input string from the beginning
 * up to (but not including) the '=' character. The returned substring
 * represents the environment variable.
 */
char	*get_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

/**
 * Finds the index of a given variable in the environment array.
 */
int	find_var(char **env, char *var)
{
	int		i;
	char	*env_var;

	i = 0;
	while (env[i])
	{
		env_var = get_env_var(env[i]);
		if (ft_strcmp(env_var, var) == 0)
			return (i);
		free(env_var);
		i++;
	}
	return (-1);
}

/**
 * Updates the environment variable with the given argument.
 * If the variable already exists, its value is updated.
 * If the variable does not exist, a new variable is added to the environment.
 */
void	update_env(char ***env, char *arg)
{
	char	*var_name;
	int		index;

	var_name = get_env_var(arg);
	index = find_var((*env), var_name);
	free(var_name);
	if (index >= 0)
		update_env_str(&(*env)[index], arg);
	else
		add_new_arg(env, arg);
}
