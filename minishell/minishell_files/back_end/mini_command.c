/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/21 15:52:36 by yadereve         ###   ########.fr       */
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
	if (args[0])
		data->exit = true;
}

void	update_env(char *arg, t_data *data)
{
	char	**env;
	char	*buff;
	char	*new_oldpwd;
	char	*new_pwd;
	int		i;

	i = 0;
	env = data->env;
	data->exit_code = 0;
	printf("%s\n", getenv("PWD"));
	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	buff = env[i];
	new_pwd = ft_str_char_join(env[i], '/');
	env[i] = ft_strjoin(new_pwd, arg);
	new_oldpwd = ft_substr(buff, 4, ft_strlen(buff));
	i = 0;
	while (ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	env[i] = ft_strjoin("OLDPWD=", new_oldpwd);
	free(new_pwd);
	free(new_oldpwd);
}

void	ft_chdir(char *arg, t_data *data)
{
	if (chdir(arg) != 0)
	{
		ft_putstr_fd("minishell: cd: no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(arg, STDERR_FILENO);
		data->exit_code = 1;
	}
	update_env(arg, data); //TODO

}

char	*ft_find_path(char **env, char *find)
{
	char	*str;
	char	*path;
	int		len;

	len = ft_strlen(find);
	str = ft_n_find_on_array(env, find, len);
	path = ft_substr(str, len, ft_strlen(str));
	free(str);
	return (path);
}

void	ft_cd_home(char **args, t_data *data)
{
	char *path;

	path = NULL;
	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
	{
		path = ft_find_path(data->env, "HOME=");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
			data->exit_code = 1;
		}
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = ft_find_path(data->env, "OLDPWD=");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			data->exit_code = 1;
		}
	}
	if (path)
		ft_chdir(path, data);
}

void	ft_cd(char **args, t_data *data)
{
	int i;

	i = 0;
	data->exit_code = 0;
	while (args[i])
		i++;
	if (i > 0 && i < 2)
		ft_cd_home(args, data);
	else if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too meny arguments", STDERR_FILENO);
		data->exit_code = 1;
	}
	else
		ft_chdir(args[1], data);
}
