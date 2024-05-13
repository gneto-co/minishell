/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/13 20:08:46 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_printf("%s\n", env[i++]);
	}
}

void	ft_unset(char **args)
{
	(void)	args;
}

void	ft_export(char **args)
{
	(void)	args;
}

void	ft_echo(char **args)
{
	int		i;
	bool	flag;

	flag = false;
	i = 1;
	while (!ft_strcmp(args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_printf("%s", args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (flag == false)
		ft_printf("\n");
}

void	ft_pwd(void)
{
	char	cwd[1024];

	if (getcwd(cwd, sizeof(cwd)))
		ft_printf("%s\n", cwd);
	else
		perror("getcwd");
}

void	ft_exit(char **args, t_data *data)
{
	int i;

	i = -1;
	ft_printf("exit\n");
	while (args[1] && args[1][++i])
	{
		if (!ft_isdigit(args[1][i]))
		{
			ft_putendl_fd(" numeric argument required", STDERR_FILENO);
			data->exit_code = 255;
			break ;
		}
		else if (args[1][i + 1] == '\0' && args[2])
		{
			ft_putendl_fd(" too many arguments", STDERR_FILENO);
			data->exit_code = 1;
		}
		else if (args[1][i + 1] == '\0')
			data->exit_code = ft_atoi(args[1]);
	}
	data->exit = true;
}

void	ft_cd(char **args)
{
	if (args[1] == NULL)
		ft_printf("minishell: expected argument to \"cd\"\n");
	else if (chdir(args[1]) != 0)
		perror("minishell: cd");
}
