/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 16:15:42 by yadereve          #+#    #+#             */
/*   Updated: 2024/05/28 15:14:43 by yadereve         ###   ########.fr       */
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
			ft_printf("%s\n", env[i++]);
	}
}

/**
 * This function removes the element at the specified index from the array and
 * updates the array accordingly. It dynamically allocates a new array with
 * enough space to hold the remaining elements and copies them over. The old
 * array is then freed.
 */
void	ft_array_n_delone(char ***array, int index)
{
	int		i;
	int		j;
	int		len;
	char	**new_array;

	i = 0;
	j = 0;
	len = ft_arraylen((*array));
	new_array = malloc(len * sizeof(char*));
	if (!new_array)
		return ;
	while ((*array)[i])
	{
		if (i != index)
		{
			new_array[j] = ft_strdup((*array)[i]);
			j++;
		}
		i++;
	}
	// free_array(array); //LEAK maybe, error malloc()
	*array = new_array;
}

/**
 * This function takes an array of arguments and a pointer to a data structure.
 * It iterates through the arguments and checks if each argument contains an
 * equal sign. If an argument contains an equal sign, it prints an error
 * message and sets the exit code to 1. If an argument does not contain an
 * equal sign, it searches for the variable in the environment array.
 * If the variable is found, it removes it from the environment array.
 */
void	ft_unset(char **args, t_data *data)
{
	int		i;
	int		index_env;

	i = 1;
	data->exit_code = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '='))
		{
			ft_printf("unset: %s: invalid parameter name", args[i]); //FIXME
			data->exit_code = 1;
		}
		else
		{
			index_env = find_var(data->env, args[i]);
			if (index_env >= 0)
			{
				ft_array_n_delone(&(data->env), index_env);
				continue ;
			}
		}
		i++;
	}
}

/**
 * Swaps the values of two pointers to strings.
 */
void	ft_swap(char **a, char **b)
{
	char *temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

/**
 * Sorts the given environment variable array in lexicographical order.
 */
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

/**
 * Prints the environment variables in a sorted order.
 */
void ft_print_export(char **env)
{
	char **sort_env;
	int i;

	i = 0;
	sort_env = ft_sort_env(env);
	while (sort_env[i])
		ft_printf("declare -x %s\n", sort_env[i++]);
	ft_free_array(sort_env);
}

bool	is_valid_identifier(const char *str)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[0]) || str[0] == '_')
		return (false);
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) || str[i] == '_')
			return (false);
		i++;
	}
	return (true);
}

char	*get_env_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	return (ft_substr(str, 0, i));
}

int	find_var(char **env, char *var)
{
	int		i;
	char	*env_var;

	i = 0;
	while (env[i])
	{
		env_var = get_env_var(env[i]);
		if (ft_strcmp(env_var, var) == 0)
			return (i);
		free(env_var);
		i++;
	}
	return (-1);
}

void	update_env_str(char **str, char *new_var)
{
	// if (*str)
	// 	free(*str); //LEAK maybe
	*str = ft_strdup(new_var);
}

char	**ft_create_env(char *new_var) //TODO static
{
	char	**new_env;

	new_env = malloc(2 * sizeof(char *));
	if (!new_env)
		return (NULL);
	new_env[0] = ft_strdup(new_var);
	if (new_env[0] == NULL)
		return (NULL);
	new_env[1] = NULL;
	return (new_env);
}

void	free_array(char ***array)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	if (!(*array))
		return ;
	while ((*array)[len])
		len++;
	while (i < len)
	{
		free((*array)[i]);
		i++;
	}
	free((*array));
}

void	add_new_arg(char ***env, char *new_var)
{
	int		len;
	char	**new_env;
	int		i;

	if (!(*env))
		*env = ft_create_env(new_var);
	else
	{
		i = 0;
		len = ft_arraylen(*env);
		new_env = malloc((len + 2) * sizeof(char*));
		if (!new_env)
			return ;
		while ((*env)[i])
		{
			new_env[i] = ft_strdup((*env)[i]);
			i++;
		}
		new_env[i] = ft_strdup(new_var);
		new_env[i + 1] = NULL;
		// free_array(env); //LEAK maybe, error malloc()
		*env = new_env;
	}
}

void	update_env(char ***env, char *arg)
{
	char	*var_name;
	int		index;

	var_name = get_env_var(arg);
	index = find_var((*env), var_name);
	free(var_name);
	if (index >= 0)
		update_env_str(&(*env)[index], arg);
	else
		add_new_arg(env, arg);
}

void	ft_export(char **args, t_data *data)
{
	int	i;

	i = 1;
	data->exit_code = 0;
	if (!args[1])
		ft_print_export(data->env);
	else
	{
		while (args[i])
		{
			if (is_valid_identifier(args[i]))
				update_env(&(data->env), args[i]);
			else
			{
				ft_putstr_fd("minishell: export: '", STDERR_FILENO);
				ft_putstr_fd(args[i], STDERR_FILENO);
				ft_putendl_fd("': not a valid identifier", STDERR_FILENO);
				data->exit_code = 1;
			}
			i++;
		}
	}
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
		ft_printf("%s\n", cwd);
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
void	ft_chdir(char *path, t_data *data)
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
