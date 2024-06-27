/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 11:47:52 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(t_data *data, char **arg, int process_status)
{
	char	*msg;

	msg = NULL;
	if (!ft_strcmp(arg[0], "exit"))
	{
		if (process_status == 2)
			msg = ft_multi_strjoin("\033[91m%s %s%s\033[0m\n",
					"minishell: exit:", arg[1], ": numeric argument required");
		else if (process_status == 1)
			msg = ft_multi_strjoin("\033[91m%s\033[0m\n",
					"minishell: exit: too many arguments");
	}
	data->process_status = process_status;
	ft_putstr_fd(msg, STDERR_FILENO);
	free(msg);
}

int	ft_error(int nb, char *str)
{
	char	*msg;
	char	*final_msg;

	if (nb == 1)
		msg = ft_multi_strjoin("%s",
				"minishell: syntax error, quotes are never closed");
	else if (nb == 2)
		msg = ft_multi_strjoin("%s '%s'",
				"minishell: parse error, unexpected token", str);
	else if (nb == 3)
		msg = ft_multi_strjoin("%s %s",
				"minishell: execute error, command not found:", str);
	else if (nb == 4)
		msg = ft_multi_strjoin("%s %s %s", "minishell:", str,
				"No such file or directory");
	else if (nb == 5)
		msg = ft_multi_strjoin("%s %s %s", "minishell:", str,
				"ambiguous redirect");
	else
		msg = ft_multi_strjoin("\nDeu mrd");
	final_msg = ft_multi_strjoin("%s%s%s", "\033[91m", msg, "\033[0m\n");
	ft_putstr_fd(final_msg, STDERR_FILENO);
	free(msg);
	free(final_msg);
	return (-1);
}
