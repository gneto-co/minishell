/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:02:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/03 13:42:54 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*get_system_var(char *var_name, char **env)
{
	char	*str;

	if (!var_name)
		return (NULL);
	str = ft_n_find_on_array(env, var_name, ft_strlen(var_name));
	if (!str)
		return (NULL);
	return (ft_strdup(str + ft_strlen(var_name) + 1));
}

static void	special_char_1_2_3(char **str, char **new_str)
{
	if (**str == '|')
		*new_str = ft_strdup("|");
	if (**str == '>')
	{
		if (*(*str + 1) == '>')
		{
			*new_str = ft_strdup(">>");
			(*str)++;
		}
		else
			*new_str = ft_strdup(">");
	}
	if (**str == '<')
	{
		if (*(*str + 1) == '<')
		{
			*new_str = ft_strdup("<<");
			(*str)++;
		}
		else
			*new_str = ft_strdup("<");
	}
}

static void	special_char_4(char **str, char **new_str, char **env)
{
	char	*var_name;

	var_name = NULL;
	if (**str == '$')
	{
		// if theres nothing after $ its just a $
		if (*(*str + 1) == ' ' || !*(*str + 1))
			*new_str = ft_strdup("$");
		else
		{
			// get the var name after the $
			while (*(*str + 1) != ' ' && !ft_strchr(SPECIAL_CHAR, *(*str + 1))
				&& *(*str + 1))
			{
				var_name = ft_str_char_join_free(var_name, *(*str + 1));
				(*str)++;
			}
			// get the text correspondent to $(var_name)
			// if theres nothing do nothing
			*new_str = get_system_var(var_name, env);
			free(var_name);
		}
	}
}

char	**special_char_treatment(char **array, int *str_nb, char **str,
		char **env)
{
	char	*new_str;

	/*
	options:
	1	| - new str '|'
	2	> - if there's another > : new str '>>', else: new str '>'
	3	< - if there's another < : new str '<', else: new str '<'
	4	$ - read the sequence after $ and new str (variable value),
			if there is nothing in $name it does nothing
	5	' - get all the text until find another ', new str (text)
	6	" - get all the text until find another ",
			if there is any $ take their value and use it as part of the str,
			new str (text)
	*/
	special_char_1_2_3(str, &new_str);
	special_char_4(str, &new_str, env);
	array = split_str(array, str_nb, &new_str);
	return (array);
}
