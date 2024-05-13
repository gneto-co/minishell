/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:04:12 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/13 14:16:05 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	msg_err(char *str, char *cmd, int code)
{
	ft_printf("%s%s\n", str, cmd);
	return (code);
}

int	ft_execute(char **args)
{
	if (args[0] == NULL)
		// An empty command was entered.
		return (0);
	else if (!ft_strcmp(args[0], "cd"))
		return (ft_cd(args));
	else if (!ft_strcmp(args[0], "env"))
		return (ft_env(args));
	else if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd(args));
	else if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args));
	else if (!ft_strcmp(args[0], "export"))
		return (ft_export(args));
	else if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args));
	else if (!ft_strcmp(args[0], "exit"))
		return (ft_exit(args));
	else
		return (msg_err("minishell: command not found: ", args[0], 127));
}
