/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/06 16:26:29 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_exit(char **args)
{
	t_tree *current;

	current = tree;
	while (current && current.next)
	{
		if (/* condition */)
		{
			/* code */
		}

		current = current.next;
	}

	(void)	args;
	return (0);
}

int	ft_cd(char **args)
{
	if (args[1] == NULL)
		ft_printf("minishell: expected argument to \"cd\"\n");
	else if (chdir(args[1]) != 0)
		perror("minishell: cd");
	return (1);
}

int	ft_pwd(char **args)
{
	(void)	args;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	return (1);
}
