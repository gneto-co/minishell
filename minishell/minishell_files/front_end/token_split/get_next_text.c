/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_text.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 15:08:40 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 17:46:53 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *	function: get the next next of str
 *	work with mods:
 *		1 - stop on: special chars, ' ', '\0'
 *		2 - stop on: $, '\0', '
 *		3 - stop on: '\0', "
 *
 *	· start char loop
 *		· depending on the mode break loop if find a certain character
 * 		· add actual character to new_str
 * 		· if str ended break loop
 *	· return new_str
 *
 */
char	*get_next_text(char *str, int *ii, int mod)
{
	char	*new_str;
	int		i;

	i = *ii;
	new_str = NULL;
	while (1)
	{
		if (str[i] == ' ' && mod == 1)
			break ;
		else if (ft_strchr(SPECIAL_CHAR, str[i]) && mod == 1)
			break ;
		else if ((str[i] == '$' || str[i] == '\'') && mod == 2)
			break ;
		else if (str[i] == '\"' && mod == 3)
			break ;
		new_str = ft_str_char_join_free(new_str, str[i]);
		if (!str[i])
			break ;
		i++;
		if (!str[i])
			break ;
	}
	*ii = i;
	return (new_str);
}

/*
 *	function: see why new_str is null and to the management
 *
 *	str is on a..
 * 		· end '\0' : break
 * 		· space ' ' : skip spaces
 * 		· special_char : new_str = special_char_manager
 * 			· if !new_str : error
 */
static bool	str_problem_check(t_data *data, char *str, char **new_str, int *ii)
{
	int	i;

	i = *ii;
	if (!str[i])
		return (false);
	else if (str[i] == ' ')
		while (str[i] && str[i] == ' ')
			i++;
	else if (ft_strchr(SPECIAL_CHAR, str[i]))
	{
		*new_str = special_char_manager(str, &i, data);
		if (data->error == true)
		{
			ft_printf("\n new_str -> %p\n", new_str);
			// LEAK existe um memleak quando input: a"a
			return (false);
		}
	}
	*ii = i;
	return (true);
}

/*
 *	function: get next_real_text or NULL if text ended
 *
 *	· start str loop
 * 		· new_str = get_next_text
 * 		· if !new_str : str_problem_check
 * 			· if problem_check == false : break
 * 		· if new_str : break
 * 	· return new_str
 */
char	*get_real_next_text(char *str, int *ii, t_data *data)
{
	char	*new_str;
	int		i;

	i = *ii;
	new_str = NULL;
	while (1)
	{
		new_str = get_next_text(str, &i, 1);
		if (!new_str)
			if (str_problem_check(data, str, &new_str, &i) == false)
				break ;
		if (new_str)
			break ;
	}
	*ii = i;
	return (new_str);
}
