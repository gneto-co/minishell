/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:10:45 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/03 13:42:40 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_error(void)
{
	ft_printf("\nDeu mrd\n");
}

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
		return (ft_error(), NULL);
	else
		array = temp;
	(*str_nb)++;
	array[*str_nb - 1] = *new_str;
	array[*str_nb] = NULL;
	*new_str = NULL;
	return (array);
}

char	**ft_token_split(char *str, char **env)
{
	int		str_nb;
	char	*new_str;
	char	**array;

	array = malloc(var_size('s', 1));
	array[0] = NULL;
	if (!str)
		return (array);
	str_nb = 0;
	new_str = NULL;
	while (1)
	{
		// if is a space
		if (*str == ' ' || !*str)
		{
			if (new_str)
			{
				// split new_str
				while (*(str + 1) == ' ')
					str++;
				array = split_str(array, &str_nb, &new_str);
			}
			if (!*str)
				break ;
		}
		// if actual char is a special char
		else if (ft_strchr(SPECIAL_CHAR, *str))
		{
			// if there is something on new_str slit it
			if (new_str)
				array = split_str(array, &str_nb, &new_str);
			// do a special treatment for each char
			array = special_char_treatment(array, &str_nb, &str, env);
		}
		// if is a regular char
		else
		{
			// put it into new_str
			new_str = ft_str_char_join_free(new_str, *str);
		}
		str++;
	}
	return (array);
}
