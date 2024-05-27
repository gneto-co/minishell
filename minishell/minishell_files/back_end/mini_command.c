/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/27 14:49:59 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//MARK ft_ls
void	ft_ls(t_data *data)
{
	DIR *d;
	struct dirent *dir;

	data->exit_code = 0;
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
		data->exit_code = EXIT_FAILURE;
	}
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
			ft_printf(env[i++]);
	}
}

void	ft_unset(char **args, t_data *data)
{
	(void)	args;
	data->exit_code = 0;
}

void	ft_swap(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

char	**ft_sort_env(char **env)
{
	char	**sort_env;
	int		len;
	int		i;
	int		j;

	i = -1;
	len = ft_arraylen(env);
	sort_env = (char **)ft_calloc(len, sizeof(char*));
	while(env[++i])
		sort_env[i] = ft_strdup(env[i]);
	sort_env[len] = NULL;
	i = 0;
	while (i < len - 1)
	{
		j = 0;
		while (j < len - 1 - i)
		{
			if (ft_strcmp(sort_env[j], sort_env[j + 1]) > 0)
				ft_swap(&sort_env[j], &sort_env[j + 1]);
			j++;
		}
		i++;
	}
	return (sort_env);
}

void	ft_print_export(char **env)
{
	char	**sort_env;
	int		i;

	i = 0;
	sort_env = ft_sort_env(env);
	while (sort_env[i])
		ft_printf("declare -x %s\n", sort_env[i++]);
	ft_free_array(sort_env);
}

void	ft_export(char **args, t_data *data)
{
	data->exit_code = 0;
	if (!args[1])
		ft_print_export(data->env);
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
		ft_printf(args[i]);
		if (args[++i])
			ft_printf(" ");
	}
	if (flag == false)
		ft_printf("\n");
}

/**
 * Prints the current working directory to the standard output.
 * If successful, the current working directory is printed.
 * If an error occurs, an error message is printed.
 */
void	ft_pwd(t_data *data)
{
	char	cwd[PATH_MAX];

	data->exit_code = 0;
	if (getcwd(cwd, sizeof(cwd)))
		ft_printf(cwd);
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
	ft_printf("exit");
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
