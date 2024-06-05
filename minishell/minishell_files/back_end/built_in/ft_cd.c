/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:47 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/05 08:54:52 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/**
 * Updates the environment variables for the current working directory (PWD)
 * and the previous working directory (OLDPWD).
 */
// FIXME not fix all error
void	cd_update_env(t_data *data)
{
	char	**env;
	char	*buff;
	char	*new_oldpwd;
	int		i;
	char	cwd[PATH_MAX];

	i = 0;
	env = data->env;
	while (env[i] && ft_strncmp(env[i], "PWD=", 4))
		i++;
	if (env[i])
	{
		buff = env[i];
		env[i] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
		free(buff);
	}
	i = 0;
	while (env[i] && ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	if (env[i])
	{
		new_oldpwd = ft_substr(buff, 4, ft_strlen(buff));
		env[i] = ft_strjoin("OLDPWD=", new_oldpwd);
		free(new_oldpwd);
	}
}

/**
 * Changes the current working directory to the specified path.
 * If the path does not exist, an error message is printed to stderr.
 */
void	ft_chdir(char *path, t_data *data)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		data->process_status = 1;
	}
	else
		cd_update_env(data);
}

/**
 * Changes the current working directory.
 */
void	cd_dir(char **args, t_data *data)
{
	char	*path;

	path = NULL;
	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
			data->process_status = 1;
		}
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			data->process_status = 1;
		}
	}
	else
		path = args[1];
	if (path)
		ft_chdir(path, data);
}

/**
 * Changes the current working directory.
 *
 * This function is responsible for changing the current working directory
 * based on the provided arguments. It checks the number of arguments and
 * displays an error message if there are too many arguments. If the number of
 * arguments is valid, it calls the `cd_dir` function to perform the actual
 * directory change.
 */
void	ft_cd(char **args, t_data *data)
{
	int	i;

	i = 0;
	data->process_status = 0;
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too meny arguments", STDERR_FILENO);
		data->process_status = 1;
	}
	else
		cd_dir(args, data);
}
