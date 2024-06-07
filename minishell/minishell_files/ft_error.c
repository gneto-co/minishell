/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/06 15:52:33 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
