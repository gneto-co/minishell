/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 10:08:24 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/23 10:46:28 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	handle_sigint(int sig)
{
	char	*prompt_str;

	(void)sig;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	printf("\n");
	prompt_str = get_prompt_text();
	ft_putstr(prompt_str);
	free(prompt_str);
}

void	handle_sigquit(int sig)
{
	(void)sig;
}
