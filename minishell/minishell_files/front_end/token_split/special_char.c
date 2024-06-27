/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:02:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 12:37:49 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * 	works for:
 * 	· pipe |
 * 	· great >
 * 	· greatgreat >>
 * 	· less >
 * 	· lessless >>
 *
 */
static char	*special_char_1_2_3(char *str, int *ii)
{
	int		i;
	char	*new_str;

	i = *ii;
	new_str = NULL;
	if (str[i] == '|')
		new_str = ft_strdup("|");
	if (str[i] == '>')
	{
		if (str[i + 1] == '>')
			new_str = (i++, ft_strdup(">>"));
		else
			new_str = ft_strdup(">");
	}
	if (str[i] == '<')
	{
		if (str[i + 1] == '<')
			new_str = (i++, ft_strdup("<<"));
		else
			new_str = ft_strdup("<");
	}
	*ii = i + 1;
	return (new_str);
}

static void	cs1(t_data *data, char **new_str, char *var_name)
{
	if (data->signal_mod == 0)
	{
		*new_str = ft_getenv(var_name, data->env);
		if (!*new_str)
			*new_str = ft_strdup("");
	}
	else
		*new_str = ft_multi_strjoin("$%s", var_name);
}

/*
 * 	works for:
 * 	· $
 *
 */
char	*special_char_4(char *str, int *ii, t_data *data)
{
	int		i;
	char	*var_name;
	char	*new_str;

	i = *ii + 1;
	var_name = NULL;
	new_str = NULL;
	if (!str[i] || str[i] == ' ' || ft_strchr(SPECIAL_CHAR, str[i]))
		new_str = ft_strdup("$");
	else if (str[i] == '?')
		new_str = (i++, ft_itoa(data->process_status));
	else
	{
		var_name = get_next_text(str, &i, 1);
		if (var_name)
			cs1(data, &new_str, var_name);
		free(var_name);
	}
	return (*ii = i, new_str);
}

/*
 * 	function : get the string for each case
 *
 * 	options:
 * 	1	| - new str '|'
 * 	2	> - if there's another > : new str '>>', else: new str '>'
 * 	3	< - if there's another < : new str '<', else: new str '<'
 * 	4	$ - read the sequence after $ and new str (variable value),
 * 			if there is nothing in $name it does nothing
 * 	5	' - get all the text until find another ', new str (text)
 * 	6	" - get all the text until find another ",
 * 			if there is any $ take their value and use it as part of the str,
 * 			new str (text)
 */
char	*special_char_manager(char *str, int *ii, t_data *data)
{
	char	*new_str;
	int		i;

	i = *ii;
	new_str = NULL;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		new_str = special_char_1_2_3(str, &i);
	else if (str[i] == '$')
		new_str = special_char_4(str, &i, data);
	else if (str[i] == '\'')
		new_str = special_char_5_6(str, &i, data, '\'');
	else if (str[i] == '\"')
		new_str = special_char_5_6(str, &i, data, '\"');
	*ii = i;
	return (new_str);
}
