/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/15 14:48:27 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_env(char **env, t_data *data)
{
	int i;

	i = 0;
	data->exit_code = 0;
	while (env && env[i])
	{
		if (ft_strchr(env[i], '='))
			ft_putendl_fd(env[i++], STDOUT_FILENO);
	}
}

void	ft_unset(char **args, t_data *data)
{
	(void)	args;
	data->exit_code = 0;
}

void	ft_export(char **args, t_data *data)
{
	(void)	args;
	data->exit_code = 0;
}

void	ft_echo(char **args, t_data *data)
{
	int		i;
	bool	flag;

	i = 1;
	flag = false;
	data->exit_code = 0;
	while (!ft_strcmp(args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[++i])
			ft_putstr_fd(" ", STDOUT_FILENO);
	}
	if (flag == false)
		ft_putstr_fd("\n", STDOUT_FILENO);
}

void	ft_pwd(t_data *data)
{
	char	cwd[1024];

	data->exit_code = 0;
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		perror("getcwd");
}

void	ft_exit(char **args, t_data *data)
{
	int i;

	i = -1;
	data->exit_code = 0;
	ft_putendl_fd("exit", STDOUT_FILENO);
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
			break ;
		}
		else if (args[1][i + 1] == '\0')
		{
			data->exit_code = ft_atoi(args[1]);
			data->exit = true;
		}
	}
}

void	ft_cd_home(char **args, t_data *data)
{
	int i;
	char *str;
	char **envs;

	envs = data->env;
	i = 0;
	str = NULL;
	while (envs[i])
	{
		if (!ft_strncmp(envs[i], "HOME=", 5))
		{
			str = ft_substr(envs[i], 5, ft_strlen(envs[i]));
			break ;
		}
		i++;
	}
	args[1] = str;
	args[2] = NULL;
	ft_cd(args, data);
}

void update_env(char **args, t_data *data)
{
	char	**envs;
	// char	*str;
	int		i;

	(void)args;
	i = 0;
	envs = data->env;
	while (envs[i])
	{
		i++;
	}
	printf("%d\n", i);
}

void	ft_cd(char **args, t_data *data)
{
	int i;

	i = 0;
	data->exit_code = 0;
	while (args[i])
		i++;
	if (i == 1)
		ft_cd_home(args, data);
	else if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too meny arguments", STDERR_FILENO);
		data->exit_code = 1;
	}
	else if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		data->exit_code = 1;
	}
	update_env(args, data);
}
