/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:13:37 by yadereve          #+#    #+#             */
/*   Updated: 2024/07/22 17:45:12 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_handle(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDERR_FILENO, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

/**
 * signal(SIGQUIT, SIG_IGN);
	IGNOR
		signal(SIGINT, SIG_IGN);
	CHILD
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	DEF
		signal(SIGINT, sigint_handle);
 */
void	signals(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	if (sig == IGNOR)
		signal(SIGINT, SIG_IGN);
	else if (sig == CHILD)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (DEF)
		signal(SIGINT, sigint_handle);
}
