/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/13 14:25:39 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(char **args)
{
	(void)	args;
	return (0);
}

int	ft_unset(char **args)
{
	(void)	args;
	return (0);
}

int	ft_export(char **args)
{
	(void)	args;
	return (0);
}

int	ft_echo(char **args)
{
	int	i;

	i = 1;
	if (args[1] != NULL)
	{
		if (!ft_strcmp(args[1], "&?"))
		{
			ft_printf("%d", ft_data()->exit_code);
			return (0);
		}
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_putchar(' ');
	}
	ft_putchar('\n');
	return(0);
}

int	ft_pwd(char **args)
{
	(void)	args;
	char	cwd[1024];

	getcwd(cwd, sizeof(cwd));
	ft_printf("%s\n", cwd);
	return (0);
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
	{
		ft_data()->exit = false;
		return (ft_atoi(args[1]));
	}
	else
	{
		ft_data()->exit = false;
		return (0);
	}
}

int	ft_cd(char **args)
{
	if (args[1] == NULL)
		ft_printf("minishell: expected argument to \"cd\"\n");
	else if (chdir(args[1]) != 0)
		perror("minishell: cd");
	return (0);
}
