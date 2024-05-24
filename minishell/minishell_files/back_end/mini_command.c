/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/23 11:25:25 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <dirent.h>

//MARK ft_ls
int	ft_ls(void)
{
	DIR *d;
	struct dirent *dir;

	d = opendir(".");
	if (d)
	{
		while ((dir = readdir(d)) != NULL)
			printf("%s\n", dir->d_name);
		closedir(d);
	}
	else
	{
		perror("minishell: opendir");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}

//MARK print_array
void	ft_print_array(char **array)
{
	int i;

	i = 0;
	while (array[i])
		printf("array: %s\n", array[i++]);
}

/**
 * Prints the environment variables to the standard output.
 */
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

/**
 * This function prints the arguments to the standard output, separated by
 * spaces. If the "-n" flag is provided as the first argument, the newline
 * character is not printed at the end.
 */
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

/**
 * Prints the current working directory to the standard output.
 * If successful, the current working directory is printed.
 * If an error occurs, an error message is printed.
 */
void	ft_pwd(t_data *data)
{
	char	cwd[1024];

	data->exit_code = 0;
	if (getcwd(cwd, sizeof(cwd)))
		ft_putendl_fd(cwd, STDOUT_FILENO);
	else
		perror("minishell: getcwd");
}

/**
 * This function is responsible for exiting the program with a specified exit
 * code. It takes an array of arguments and a pointer to a data structure as
 * parameters. The function checks if the first argument is a valid numeric
 * value and sets the exit code accordingly. If the first argument is not a
 * valid numeric value, it prints an error message to the standard error and
 * sets the exit code to 255. If there are more than one argument, it prints
 * an error message to the standard error and sets the exit code to 1.
 * If the first argument is a valid numeric value and there are no more
 * arguments, it sets the exit code to the converted value and sets the exit
 * flag to true. If there are no arguments, it sets the exit flag to true.
 */
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

/**
 * Updates the environment variables for the current working directory (PWD)
 * and the previous working directory (OLDPWD).
 */
// TODO не продумані всі варіанти помилок
void	cd_update_env(t_data *data)
{
	char	**env;
	char	*buff;
	char	*new_oldpwd;
	int		i;
	char	cwd[1024];

	i = 0;
	env = data->env;
	while (ft_strncmp(env[i], "PWD=", 4))
		i++;
	buff = env[i];
	env[i] = ft_strjoin("PWD=", getcwd(cwd, sizeof(cwd)));
	new_oldpwd = ft_substr(buff, 4, ft_strlen(buff));
	i = 0;
	while (ft_strncmp(env[i], "OLDPWD=", 7))
		i++;
	env[i] = ft_strjoin("OLDPWD=", new_oldpwd);
	free(new_oldpwd);
}

/**
 * Changes the current working directory to the specified path.
 * If the path does not exist, an error message is printed to stderr.
 */
void ft_chdir(char *path, t_data *data)
{
	if (chdir(path) != 0)
	{
		ft_putstr_fd("minishell: cd: ", STDERR_FILENO);
		ft_putstr_fd("no such file or directory: ", STDERR_FILENO);
		ft_putendl_fd(path, STDERR_FILENO);
		data->exit_code = 1;
	}
	else
		cd_update_env(data);
}

/**
 * Changes the current working directory.
 */
void	cd_dir(char **args, t_data *data)
{
	char *path;

	path = NULL;
	if (args[1] == NULL || !ft_strcmp(args[1], "~"))
	{
		path = getenv("HOME");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: HOME not set", STDERR_FILENO);
			data->exit_code = 1;
		}
	}
	else if (!ft_strcmp(args[1], "-"))
	{
		path = getenv("OLDPWD");
		if (!path)
		{
			ft_putstr_fd("minishel: cd: OLDPWD not set", STDERR_FILENO);
			data->exit_code = 1;
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
	int i;

	i = 0;
	data->exit_code = 0;

	// ft_print_array(args); //MARK ft_cd
	while (args[i])
		i++;
	if (i > 2)
	{
		ft_putendl_fd("minishell: cd: too meny arguments", STDERR_FILENO);
		data->exit_code = 1;
	}
	else
		cd_dir(args, data);
}
