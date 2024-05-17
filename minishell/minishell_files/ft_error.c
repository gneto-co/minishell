/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 16:00:18 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int nb, char *str)
{
	if (nb == 1)
		ft_printf("\033[91m%s\033[0m\n", "minishell: parse error, "
			"quotes are never closed");
	else if (nb == 2)
		ft_printf("\033[91m%s '%s'\033[0m\n", "minishell: parse error, "
			"unexpected token", str);
	else if (nb == 3)
		ft_printf("\033[91m%s %s\033[0m\n", "minishell: execute error, "
			"command not found:", str);
	else
		ft_printf("\nDeu mrd\n");
	return (-1);
}
