/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:04:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/13 20:05:28 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execute(char **args, t_data *data, char **env)
{
	if (!ft_strcmp(args[0], "cd"))
		ft_cd(args);
	else if (!ft_strcmp(args[0], "env"))
		ft_env(env);
	else if (!ft_strcmp(args[0], "pwd"))
		ft_pwd();
	else if (!ft_strcmp(args[0], "echo"))
		ft_echo(args);
	else if (!ft_strcmp(args[0], "export"))
		ft_export(args);
	else if (!ft_strcmp(args[0], "unset"))
		ft_unset(args);
	else if (!ft_strcmp(args[0], "exit"))
		ft_exit(args, data);
	else
		perror("command not found ");
	printf("%d\n", data->exit_code);
}
