/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_token_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/29 10:10:45 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/16 17:45:25 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 *	· if isn't more text in a row
 *		· return false
 *	· if is more text in a row
 *		· return true
 */
static bool	have_more_text(char *str, int i)
{
	if (str[i - 1] == '|' || str[i - 1] == '<' || str[i - 1] == '>')
		return (false);
	if (str[i] == '$' || str[i] == '\'' || str[i] == '\"')
		return (true);
	else if (ft_strchr(SPECIAL_CHAR, str[i])
		|| str[i] == ' ' || str[i] == '\0')
		return (false);
	else
		return (true);
}

/*
 *	function: puts the new_str into the array
 *	· if !new_str
 *		· return array the just like it was
 *	· realloc array with a new string pointer
 *	· error check
 *	· put new_str on new pointer of array
 *	· set array last pointer to NULL
 *	· return array
 */
char	**split_str(char **array, int *str_nb, char *new_str)
{
	char	**temp;

	if (!new_str)
		return (array);
	temp = NULL;
	temp = ft_realloc(array, var_size('s', *str_nb + 1), var_size('s', *str_nb
				+ 2));
	if (temp == NULL)
		return (ft_error(0, NULL), NULL);
	else
		array = temp;
	(*str_nb)++;
	array[*str_nb - 1] = new_str;
	array[*str_nb] = NULL;
	return (array);
}

/* initialize ft_tokens_split data */
static void	data_initialize(int *i, int *str_nb, char **new_str, char ***array)
{
	*i = 0;
	*str_nb = 0;
	*new_str = NULL;
	*array = malloc(var_size('s', 1));
	*array[0] = NULL;
}

/* that function only exists do decrease function lines */
static void	free_new_str(char **new_str)
{
	if (*new_str)
		free(*new_str);
}

/*
 * 	function : receive the input str and divide it into tokens (string array)
 * 	if error : return (0);
 *
 * 	· initialize data and check for errors
 * 	· start loop
 * 	· get real_text to temp_str
 * 	· if !temp_str : break
 * 	· new_str = new_str + temp_str
 * 	· if isn't more text in a row
 * 		· put new_str on array
 * 	· else
 * 		· do nothing so we can get more text to new_str
 */
char	**ft_token_split(char *str, t_data *data)
{
	int		i;
	int		str_nb;
	char	*temp_str;
	char	*new_str;
	char	**array;

	data_initialize(&i, &str_nb, &new_str, &array);
	if (!str)
		return (array);
	while (1)
	{
		temp_str = get_real_next_text(str, &i, data);
		if (!temp_str)
			return (free_new_str(&new_str), array);
		new_str = ft_strjoin_free(new_str, temp_str);
		free(temp_str);
		if (!have_more_text(str, i))
		{
			array = split_str(array, &str_nb, new_str);
			new_str = NULL;
		}
	}
	return (array);
}
