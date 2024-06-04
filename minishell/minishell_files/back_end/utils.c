/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 22:05:25 by yadereve          #+#    #+#             */
/*   Updated: 2024/06/04 22:57:28 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_or_exit_update_env(char ***env, char *cmd)
{
	char	*buff;
	char	*num;
	int		val;
	int		index;

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
