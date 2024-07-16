/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 13:13:37 by yadereve          #+#    #+#             */
/*   Updated: 2024/07/16 13:47:57 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sigint_handle(int sig)
{
	if (sig == SIGINT)
	{
		// printf("pid = %d\n", getpid()); // MARK pid =
		write(STDERR_FILENO, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	signals(int sig)
{
	signal(SIGQUIT, SIG_IGN);
	if (sig == ignor)
		signal(SIGINT, SIG_IGN);
	else if (sig == child)
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
	}
	else if (def)
		signal(SIGINT, sigint_handle);
}
