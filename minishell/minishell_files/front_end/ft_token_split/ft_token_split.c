/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:10:45 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/03 16:40:45 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// puts a new_str into the array
char	**split_str(char **array, int *str_nb, char **new_str)
{
	char	**temp;

	if (!*new_str)
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
	array[*str_nb - 1] = *new_str;
	array[*str_nb] = NULL;
	*new_str = NULL;
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

char	**ft_token_split(char *str, char **env)
{
	int		i;
	int		str_nb;
	char	*new_str;
	char	**array;

	// initializations
	i = 0;
	str_nb = 0;
	new_str = NULL;
	array = malloc(var_size('s', 1));
	array[0] = NULL;
	// error management
	if (!str)
		return (array);
	// str read
	while (1)
	{
		//
		// try to get a new str
		//
		new_str = get_next_text(str, &i, 1);
		// ft_printf("\n╭─┤new_str├───┤%s├\n│\n", new_str);
		//
		// if we got a new str: put it on array
		//
		if (new_str)
		{
			array = split_str(array, &str_nb, &new_str);
			// ft_printf("╰──str_nb──► %d\n\n", str_nb);
		}
		//
		// if theres no new str see why
		//
		else
		{
			// ft_printf("╰──str[i]────¦%c¦─\n\n", str[i]);
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
				array = split_str(array, &str_nb, &new_str);
				// ft_printf("╰──str_nb──► %d\n\n", str_nb);
			}
		}
		// getchar();
	}
	return (array);
}
