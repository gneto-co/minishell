/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:10:45 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/30 16:20:55 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_error(void)
{
	ft_printf("\nDeu mrd\n");
}

static char	**split_str(char **array, int *str_nb, char **new_str)
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

static char	*get_system_var(char *var_name)
{
	return (ft_strdup(var_name));
}

static char	**special_char_treatment(char **array, int *str_nb, char **str)
{
	char	*new_str;
	char	*var_name;

	/*
	options:
		| - new str '|'
		> - if there's another > : new str '>>', else: new str '>'
		< - if there's another < : new str '<', else: new str '<'
		$ - read the sequence after $ and new str (variable value),
			if there is nothing in $name it does nothing
		' - get all the text until find another ', new str (text)
		" - get all the text until find another ",
			if there is any $ take their value and use it as part of the str,
			new str (text)
	*/
	var_name = NULL;
	if (**str == '|')
		new_str = ft_strdup("|");
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			new_str = ft_strdup(">>");
			(*str)++;
		}
		else
			new_str = ft_strdup(">");
	}
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			new_str = ft_strdup("<<");
			(*str)++;
		}
		else
			new_str = ft_strdup("<");
	}
	if (**str == '$')
	{
		if (*(*str + 1) == ' ' || !*(*str + 1))
			new_str = ft_strdup("$");
		else
		{
			while (*(*str + 1) != ' ' && !ft_strchr(SPECIAL_CHAR, *(*str + 1))
				&& *(*str + 1))
			{
				var_name = ft_str_char_join_free(var_name, *(*str + 1));
				(*str)++;
			}
			new_str = get_system_var(var_name);
			free(var_name);
		}
	}
	// if (**str == '\'')
	// {
	// 	if (!*(*str + 1))
	// 		ft_printf("pede mais texto");
	// 	while (*(*str + 1) != '\'')
	// 	{
	// 		new_str = ft_str_char_join_free(new_str, *(*str + 1));
	// 		(*str)++;
			
	// 	}
	// }
	array = split_str(array, str_nb, &new_str);
	return (array);
}

char	**ft_token_split(char *str)
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
			array = special_char_treatment(array, &str_nb, &str);
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
