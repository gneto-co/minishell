/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:10:45 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 10:24:30 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// if the str is over: return false
// else: return true
static bool	have_more_text(char *str, int i)
{
	if (str[i - 1] == '|' || str[i - 1] == '<' || str[i - 1] == '>')
		return (false);
	if (str[i] == '$' || str[i] == '\'' || str[i] == '\"')
		return (true);
	else if (ft_strchr(SPECIAL_CHAR, str[i]) || str[i] == ' ' || str[i] == '\0')
		return (false);
	else
		return (true);
}

// puts a new_str into the array
char	**split_str(char **array, int *str_nb, char *new_str)
{
	char	**temp;

	if (!new_str)
		return (array);
	temp = NULL;
	// split new_str

	temp = ft_realloc(array, var_size('s', *str_nb + 1), var_size('s', *str_nb
				+ 2));
	if (temp == NULL)
		return (ft_error(0), NULL);
	else
		array = temp;
	(*str_nb)++;
	array[*str_nb - 1] = new_str;
	array[*str_nb] = NULL;
	return (array);
}

// mod:
// 1 - stop on: special chars, ' ', '\0'
// 2 - stop on: $, '\0', '
// 3 - stop on: '\0', "
char	*get_next_text(char *str, int *ii, int mod)
{
	char	*new_str;
	int		i;

	i = *ii;
	new_str = NULL;
	while (1)
	{
		// char creak check
		if (str[i] == ' ' && mod == 1)
			break ;
		else if (ft_strchr(SPECIAL_CHAR, str[i]) && mod == 1)
			break ;
		else if ((str[i] == '$' || str[i] == '\'') && mod == 2)
			break ;
		else if (str[i] == '\"' && mod == 3)
			break ;
		// char increment
		new_str = ft_str_char_join_free(new_str, str[i]);
		// end check
		if (!str[i])
			break ;
		else
			i++;
	}
	*ii = i;
	return (new_str);
}

// that function will return the next text, or NULL if theres no more text
static char	*get_real_next_text(char *str, int *ii, t_data *data, char **env)
{
	char	*new_str;
	int		i;

	i = *ii;
	new_str = NULL;
	while (1)
	{
		//
		// try to get a new str
		//
		new_str = get_next_text(str, &i, 1);
		//
		// if theres no new str see why
		//
		if (!new_str)
		{
			// if there is no str left: end the cycle
			if (!str[i])
				break ;
			// if str is on a space: skip all the spaces
			else if (str[i] == ' ')
				while (str[i] && str[i] == ' ')
					i++;
			// if str is a special char: special char treatment
			else if (ft_strchr(SPECIAL_CHAR, str[i]))
			{
				new_str = special_char_treatment(str, &i, env);
				if (!new_str)
				{
					data->error = true;
					break ;
				}
			}
		}
		if (new_str)
			break ;
	}
	*ii = i;
	return (new_str);
}

// receive a str and the env
// it will split all the args into a array
// if there is some kind of error: return NULL
char	**ft_token_split(char *str, t_data *data, char **env)
{
	int		i;
	int		str_nb;
	char	*temp_str;
	char	*new_str;
	char	**array;

	// initializations
	i = 0;
	str_nb = 0;
	temp_str = NULL;
	new_str = NULL;
	array = malloc(var_size('s', 1));
	array[0] = NULL;
	// error management
	if (!str)
		return (array);
	// str read
	while (1)
	{
		temp_str = get_real_next_text(str, &i, data, env);
		if (!temp_str)
			break ;
		new_str = ft_strjoin_free(new_str, temp_str);
		free(temp_str);
		// if there is no more text followed: split_str
		if (!have_more_text(str, i))
		{
			array = split_str(array, &str_nb, new_str);
			new_str = NULL;
		}
	}
	return (array);
}
