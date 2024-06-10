/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/10 17:35:42 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(t_data *data, char **arg, int process_status)
{
	char *msg;

	msg = NULL;
	if (!ft_strcmp(arg[0], "exit"))
	{
		if (process_status == 2)
			msg = ft_multi_strjoin("\033[91m%s %s%s\033[0m\n", "minishell: exit:", arg , ": numeric argument required");
		else if (process_status == 1)
			msg = ft_multi_strjoin("\033[91m%s\033[0m\n", "minishell: exit: too many arguments");
	}
	data->process_status = process_status;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

int	ft_error(int nb, char *str)
{
	char *msg;
	if (nb == 1)
		msg = ft_multi_strjoin("\033[91m%s\033[0m\n", "minishell: syntax error, "
			"quotes are never closed");
	else if (nb == 2)
		msg = ft_multi_strjoin("\033[91m%s '%s'\033[0m\n", "minishell: parse error, "
			"unexpected token", str);
	else if (nb == 3)
		msg = ft_multi_strjoin("\033[91m%s %s\033[0m\n", "minishell: execute error, "
			"command not found:", str);
	else if (nb == 4)
		msg = ft_multi_strjoin("\033[91m%s %s %s\033[0m\n", "minishell:", str , "No such file or directory");
	else
		msg = ft_multi_strjoin("\033[91m\nDeu mrd\033[0m\n");
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
	return (-1);
}
