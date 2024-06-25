/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 18:20:02 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/25 12:10:36 by yadereve         ###   ########.fr       */
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
void	ft_print_export(char **env, t_data *data)
{
	char	**sort_env;
	int		i;

	i = 0;
	sort_env = ft_sort_env(env);
	while (sort_env[i])
	{
		ft_putout("declare -x ", data);
		ft_putout(sort_env[i++], data);
		ft_putout("\n", data);
	}
	ft_free_array(sort_env);
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
	if (!args[1])
		ft_print_export(data->env, data);
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
