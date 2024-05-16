/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:02:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 18:13:31 by gneto-co         ###   ########.fr       */
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

/*
 * 	works for:
 * 	· $
 *
 */
static char	*special_char_4(char *str, int *ii, t_data *data)
{
	int		i;
	char	*var_name;
	char	*new_str;

	i = *ii;
	var_name = NULL;
	new_str = NULL;
	i++;
	if (!str[i] || str[i] == ' ')
		new_str = ft_strdup("$");
	else
	{
		var_name = get_next_text(str, &i, 1);
		if (var_name)
			new_str = ft_get_system_var(var_name, data->env);
		free(var_name);
	}
	*ii = i;
	return (new_str);
}

/*
 * 	works for:
 * 	· ''
 *
 */
static char	*special_char_5(char *str, int *ii, t_data *data)
{
	char	*new_str;
	char	*text_read;
	char	*var_read;
	int		i;

	i = *ii;
	new_str = NULL;
	text_read = NULL;
	// skip '
	i++;
	while (1)
	{
		// get text from str
		text_read = get_next_text(str, &i, 2);
		// if we got text put it on newstr
		if (text_read)
		{
			new_str = ft_strjoin_free(new_str, text_read);
			free(text_read);
		}
		// if theres not see why
		else
		{
			if (!str[i])
			{
				ft_error(1, NULL);
				data->error = true;
				free(new_str);
				free(text_read);
				new_str = NULL;
				break ;
			}
			else if (str[i] == '\'')
			{
				i++;
				break ;
			}
			else if (str[i] == '$')
			{
				var_read = special_char_4(str, &i, data);
				new_str = ft_strjoin_free(new_str, var_read);
				free(var_read);
			}
		}
	}
	*ii = i;
	return (new_str);
}

/*
 * 	works for:
 * 	· ""
 *
 */
static char	*special_char_6(char *str, int *ii, t_data *data)
{
	char	*new_str;
	char	*text_read;
	int		i;

	i = *ii;
	new_str = NULL;
	text_read = NULL;
	// skip '
	i++;
	while (1)
	{
		// get text from str
		text_read = get_next_text(str, &i, 3);
		// if we got text put it on newstr
		if (text_read)
		{
			new_str = ft_strjoin_free(new_str, text_read);
			free(text_read);
		}
		// if theres not see why
		else
		{
			if (!str[i])
			{
				ft_error(1, NULL);
				data->error = true;
				free(new_str);
				free(text_read);
				new_str = NULL;
				break ;
			}
			else if (str[i] == '\"')
			{
				i++;
				break ;
			}
		}
	}
	*ii = i;
	return (new_str);
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
		new_str = special_char_5(str, &i, data);
	else if (str[i] == '\"')
		new_str = special_char_6(str, &i, data);
	*ii = i;
	return (new_str);
}