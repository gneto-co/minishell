/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 14:47:17 by gneto-co         ###   ########.fr       */
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
	else
		ft_printf("\nDeu mrd\n");
	if (str)
		free(str);
	return (-1);
}
