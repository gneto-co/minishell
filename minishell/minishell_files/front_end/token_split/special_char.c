/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:02:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/24 16:05:27 by gneto-co         ###   ########.fr       */
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

	(void)data;
	(void)var_name;
	i = *ii;
	var_name = NULL;
	new_str = NULL;
	i++;
	if (!str[i] || str[i] == ' ')
		new_str = ft_strdup("$");
	else
	{
		new_str = ft_strdup("$");
		new_str = ft_strjoin_free(new_str, get_next_text(str, &i, 1));
	}
	// else if (str[i] == '?')
	// {
	// 	new_str = ft_itoa(data->process_status);
	// 	i++;
	// }
	// else
	// {
	// new_str = get_next_text(str, &i, 1);
	// 	if (var_name)
	// 	{
	// 		new_str = ft_get_system_var(var_name, data->env);
	// 		// MARK
	// 		// dar split
	// 	}
	// 	free(var_name);
	// }
	*ii = i;
	return (new_str);
}

/* this 2 struct and function only exist because of norminette */
typedef struct s_temp
{
	int		*ii;
	char	*str;
	char	**new_str;
	char	**text_read;
	char	**var_read;
}			t_temp;
typedef struct s_temp2
{
	char	*temp_str;
	char	*new_str;
	char	*text_read;
	char	*var_read;
}			t_temp2;

static bool	problem_check(t_data *data, t_temp temp, char c)
{
	int		i;
	bool	b;

	b = false;
	i = *(temp.ii);
	if (!temp.str[i])
	{
		ft_error(1, NULL);
		data->error = true;
		free(*(temp.new_str));
		free(*(temp.text_read));
		*(temp.new_str) = NULL;
		b = (true);
	}
	else if (temp.str[i] == c)
		b = (i++, true);
	else if (c == '\"' && temp.str[i] == '$')
	{
		*(temp.var_read) = special_char_4(temp.str, &i, data);
		*(temp.new_str) = ft_strjoin_free(*(temp.new_str), *(temp.var_read));
		free(*(temp.var_read));
	}
	*(temp.ii) = i;
	return (b);
}

/*
 * 	works for:
 * 	· ''
 * 	· ""
 *
 */
static char	*special_char_5_6(char *str, int *ii, t_data *data, char c)
{
	t_temp2	temp;
	int		i;
	bool	b;

	b = false;
	i = *ii + 1;
	temp.text_read = NULL;
	temp.new_str = NULL;
	while (b == false)
	{
		temp.text_read = get_next_text(str, &i, c);
		if (temp.text_read)
		{
			temp.new_str = ft_strjoin_free(temp.new_str, temp.text_read);
			free(temp.text_read);
		}
		else
		{
			b = problem_check(data, (t_temp){&i, str, &temp.new_str,
					&temp.text_read, &temp.var_read}, c);
		}
	}
	*ii = i;
	ft_printf("new_str -> %s\n", temp.new_str); // MARK
	if (!temp.new_str)
		return (NULL);
	temp.temp_str = ft_multi_strjoin("%c%s", c, temp.new_str);
	free(temp.new_str);
	return (temp.temp_str);
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
