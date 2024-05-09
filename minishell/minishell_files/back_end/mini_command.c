/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/09 16:37:38 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args)
{
	(void)	args;
	return (1);
}

int	ft_unset(char **args)
{
	(void)	args;
	return (1);
}

int	ft_export(char **args)
{
	(void)	args;
	return (1);
}

int	ft_echo(char **args)
{
	// (void)	args;
	int	i;

	i = 0;
	while (args[++i])
	{
		ft_printf("%s\n", args[i]);
	}
	return(1);
}

int	ft_pwd(char **args)
{
	(void)	args;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
	return (1);
}

int	ft_exit(char **args)
{
	/* перевіляти чи останій exit*/
	// t_tree *current;

	// current = tree;
	// while (current && current.next)
	// {
	// 	if (/* condition */)
	// 	{
	// 		/* code */
	// 	}

	// 	current = current.next;
	// }

	// (void)	args;
	if (args[1])
		exit(ft_atoi(args[1]));
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
