/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 17:02:21 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 19:24:34 by yadereve         ###   ########.fr       */
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

// | < >
static char	*special_char_1_2_3(char *str, int *ii)
{
	int		i;
	char	*new_str;

	i = *ii;
	new_str = NULL;
	if (str[i] == '|')
		new_str = ft_strdup("|");
	if (str[i] == '>')
		if (str[i + 1] == '>')
		{
			new_str = ft_strdup(">>");
			i++;
		}
		else //FIXME error: add explicit braces to avoid dangling else [-Werror,-Wdangling-else]
			new_str = ft_strdup(">");
	if (str[i] == '<')
		if (str[i + 1] == '<')
		{
			new_str = ft_strdup("<<");
			i++;
		}
		else //FIXME error: add explicit braces to avoid dangling else [-Werror,-Wdangling-else]
			new_str = ft_strdup("<");
	*ii = i + 1;
	return (new_str);
}

// $
static char	*special_char_4(char *str, int *ii, char **env)
{
	int		i;
	char	*var_name;
	char	*new_str;

	i = *ii;
	var_name = NULL;
	new_str = NULL;
	// skip the $
	i++;
	// if theres nothing after $ its just a $
	if (!str[i] || str[i] == ' ')
		new_str = ft_strdup("$");
	else
	{
		// get the var name after the $
		var_name = get_next_text(str, &i, 1);
		// if theres a var_name: get the text correspondent to $(var_name)
		// if there is nothing on that name it will be NULL
		if (var_name)
			new_str = get_system_var(var_name, env);
		free(var_name);
	}
	*ii = i;
	return (new_str);
}

// '
static char	*special_char_5(char *str, int *ii, char **env)
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
		if(text_read)
		{
			new_str = ft_strjoin_free(new_str, text_read);
			free(text_read);
		}
		// if theres not see why
		else
		{
			if (!str[i])
			{
				ft_error(1);
				if (new_str)
					free(new_str);
				if (text_read)
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
				var_read = special_char_4(str, &i, env);
				new_str = ft_strjoin_free(new_str, var_read);
				free(var_read);
			}
		}
	}
	*ii = i;
	return (new_str);
}

// "
static char	*special_char_6(char *str, int *ii, char **env) //FIXME error: unused parameter 'env' [-Werror,-Wunused-parameter]
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
		if(text_read)
		{
			new_str = ft_strjoin_free(new_str, text_read);
			free(text_read);
		}
		// if theres not see why
		else
		{
			if (!str[i])
			{
				ft_error(1);
				if (new_str)
					free(new_str);
				ft_printf("-> %s \n", text_read);
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

char	*special_char_treatment(char *str, int *ii, char **env)
{
	char	*new_str;
	int		i;

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
	i = *ii;
	new_str = NULL;
	if (str[i] == '|' || str[i] == '<' || str[i] == '>')
		new_str = special_char_1_2_3(str, &i);
	else if (str[i] == '$')
		new_str = special_char_4(str, &i, env);
	else if (str[i] == '\'')
		new_str = special_char_5(str, &i, env);
	else if (str[i] == '\"')
		new_str = special_char_6(str, &i, env);
	*ii = i;
	return (new_str);
}
