/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/03 11:09:20 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Swaps the values of two pointers to strings.
 */
void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * Sorts the given environment variable array in lexicographical order.
 */
char	**ft_sort_env(char **env)
{
	char	**sort_env;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = ft_arraylen(env);
	sort_env = (char **)ft_calloc(len + 1, sizeof(char *));
	while (env[++i])
		sort_env[i] = ft_strdup(env[i]);
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(sort_env[j], sort_env[j + 1]) > 0)
				ft_swap(&sort_env[j], &sort_env[j + 1]);
			j++;
		}
		i++;
	}
	sort_env[len] = NULL;
	return (sort_env);
}

/**
 * Prints the environment variables in a sorted order.
 */
void	ft_print_export(char **env)
{
	char	**sort_env;
	int		i;

	i = 0;
	sort_env = ft_sort_env(env);
	while (sort_env[i])
	{
		ft_printf("declare -x %s\n", sort_env[i++]);
	}
	ft_free_array(sort_env);
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
 * Updates the value of a string pointer with a new variable.
 * This function takes a string pointer and a new variable as input.
 * It updates the value of the string pointer by duplicating the new variable.
 * If the string pointer was previously pointing to a string, it frees the
 * memory allocated for that string before duplicating the new variable.
 */
void	update_env_str(char **str, char *new_var)
{
	// if (*str)
	// 	free(*str); //LEAK maybe
	*str = ft_strdup(new_var);
}

/**
 * Creates a new environment variable with the given value.
 */
char	**ft_create_env(char *new_var) // TODO static
{
	char **new_env;

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
 * @brief Adds a new argument to the environment variable array.
 *
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
		free_array(env); //LEAK maybe, error malloc()
		*env = new_env;
	}
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

/**
 * This function exports environment variables based on the provided arguments.
 * If no arguments are provided, it prints all the exported variables.
 * If an argument is not a valid identifier, it prints an error message and
 * sets the exit code to 1.
 */
void	ft_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	data->process_status = 0;
	if (!args[1])
		ft_print_export(data->env);
	else
	{
		while (args[i])
		{
			if (is_valid_identifier(args[i]))
				update_env(&(data->env), args[i]);
			else
			{
				ft_putstr_fd("minishell: export: '", STDERR_FILENO);
				ft_putstr_fd(args[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
				data->process_status = 1;
			}
			i++;
		}
	}
}

