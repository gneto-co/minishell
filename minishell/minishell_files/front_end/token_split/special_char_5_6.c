/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_char_5_6.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 11:14:00 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 13:20:55 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	cs1(t_data *data, char *str, char c, t_individual_data *i_data)
{
	char	*var_read;

	if (!str[i_data->i])
	{
		data->error = (ft_error(1, NULL), true);
		free(i_data->new_str);
		free(i_data->text_read);
		i_data->b = (i_data->new_str = NULL, true);
	}
	else if (str[i_data->i] == c)
	{
		i_data->i++;
		if (!i_data->new_str)
			i_data->new_str = ft_strdup("");
		i_data->b = true;
	}
	else if (str[i_data->i] == '$')
	{
		if (c == '\"')
		{
			var_read = special_char_4(str, &i_data->i, data);
			i_data->new_str = ft_strjoin_free(i_data->new_str, var_read);
			free(var_read);
		}
	}
}

/*
 * 	works for:
 * 	· ' '
 * 	· " "
 *
 */
char	*special_char_5_6(char *str, int *ii, t_data *data, char c)
{
	t_individual_data	i_data;

	i_data.b = false;
	i_data.i = *ii + 1;
	i_data.text_read = NULL;
	i_data.new_str = NULL;
	while (i_data.b == false)
	{
		i_data.text_read = get_next_text(str, &i_data.i, c);
		if (i_data.text_read)
		{
			i_data.new_str = ft_strjoin_free(i_data.new_str, i_data.text_read);
			free(i_data.text_read);
		}
		else
			cs1(data, str, c, &i_data);
	}
	*ii = i_data.i;
	if (data->signal_mod == 2)
	{
		free(i_data.new_str);
		i_data.new_str = ft_char_dup(c);
	}
	return (i_data.new_str);
}
