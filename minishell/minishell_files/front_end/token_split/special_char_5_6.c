/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_5_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:14:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/25 11:36:18 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*
 * 	works for:
 * 	· ' '
 * 	· " "
 *
 */
char	*special_char_5_6(char *str, int *ii, t_data *data, char c)
{
	int		i;
	bool	b;
	char	*new_str;
	char	*text_read;
	char	*var_read;

	b = false;
	i = *ii + 1;
	text_read = NULL;
	new_str = NULL;
	while (b == false)
	{
		text_read = get_next_text(str, &i, c);
		if (text_read)
		{
			new_str = ft_strjoin_free(new_str, text_read);
			free(text_read);
		}
		else
		{
			if (!str[i])
			{
				ft_error(1, NULL);
				data->error = true;
				free(new_str);
				free(text_read);
				new_str = NULL;
				b = (true);
			}
			else if (str[i] == c)
			{
				i++;
                if (!new_str)
                    new_str = ft_strdup("");
				b = true;
			}
			else if (c == '\"' && str[i] == '$')
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
