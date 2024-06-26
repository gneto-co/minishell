/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:08:24 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/26 14:55:31 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/* void	handle_sigint(int sig)
{

	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	ft_putstr(PROMPT_STR);
} */

void handle_sigint(int sig) {
    (void)sig;
    rl_replace_line("", 0);
    rl_on_new_line();
    printf("\n"); // Move to a new line
    rl_redisplay();
}

void	handle_sigquit(int sig)
{
	(void)sig;
}
