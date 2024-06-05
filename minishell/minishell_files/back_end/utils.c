/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:05:25 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/05 19:22:55 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_getenv(char *name, char **env)
{
	int		index;
	char	*val;

	index = find_var(env, name);
	if (index >= 0)
		val = ft_substr(env[index], ft_strlen(name) + 1, ft_strlen(env[index]));
	else
		val = NULL;
	return (val);
}

void init_or_exit_update_env(char ***env, char *cmd)
{
	char *buff;
	char *num;
	int val;
	int index;

	index = find_var((*env), "SHLVL");
	if (index < 0)
		return ;
	buff = ft_getenv("SHLVL", (*env));
	val = ft_atoi(buff);
	free(buff);
	num = NULL;
	buff = NULL;
	if (!strcmp(cmd, "exit"))
		val--;
	else
		val++;
	num = ft_itoa(val);
	buff = ft_strjoin("SHLVL=", num);
	update_env_str(&(*env)[index], buff);
	free(buff);
	free(num);
}

void ft_putout(char *str, t_data *data)
{
	data->output_string = ft_strjoin_free(data->output_string, str);
}
