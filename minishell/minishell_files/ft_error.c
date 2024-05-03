/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 17:25:55 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/02 17:38:34 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_error(int nb)
{
	if (nb == 1)
		ft_printf("\033[91m%s\033[0m\n", "minishell: parse error,"
			"quotes are never closed");
	else
		ft_printf("\nDeu mrd\n");
	return (-1);
}
