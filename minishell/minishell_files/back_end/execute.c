/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:04:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/25 11:29:17 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(char **args, t_data *data)
{
	if (!ft_strcmp(args[0], "ls"))
		ft_ls(data);
	if (!ft_strcmp(args[0], "cd"))
		ft_cd(args, data);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(data->env, data);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd(data);
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args, data);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args,data);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args, data);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, data);
	else
		perror("command not found ");
	printf("\n\nexit code: %d\n", data->exit_code);
}
