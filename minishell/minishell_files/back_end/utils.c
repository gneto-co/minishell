/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:05:25 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/05 16:58:26 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void init_or_exit_update_env(char ***env, char *cmd)
{
	char *buff;
	char *num;
	int val;
	int index;

	buff = NULL;
	num = NULL;
	index = find_var((*env), "SHLVL");
	val = ft_atoi(getenv("SHLVL"));
	if (!strcmp(cmd, "exit"))
	{
		val--;
		num = ft_itoa(val);
		buff = ft_strjoin("SHLVL=", num);
		update_env_str(&(*env)[index], buff);
	}
	else
	{
		val++;
		num = ft_itoa(val);
		buff = ft_strjoin("SHLVL=", num);
		update_env_str(&(*env)[index], buff);
	}
	free(buff);
	free(num);
}
/*
void ft_putout(char *str, t_data *data)
{
	char *new_str;

	new_str = data->output_string;
	if (new_str)
	{
		// free(data->output_string); //LEAK
		new_str = ft_strjoin_free(new_str, str);
	}
	else
	{
		new_str = ft_strdup(str);
	}
	data->output_string = new_str;
} */

void ft_putout(char *str, t_data *data)
{
	data->output_string = ft_strjoin_free(data->output_string, str);
}
