/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:24:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/27 12:19:08 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../minishell.h"

char	*is_built_in(char *name, char **r)
{
	*r = NULL;
	if (!ft_strcmp(name, "cd"))
		*r = ft_strdup("cd");
	else if (!ft_strcmp(name, "env"))
		*r = ft_strdup("env");
	else if (!ft_strcmp(name, "pwd"))
		*r = ft_strdup("pwd");
	else if (!ft_strcmp(name, "echo"))
		*r = ft_strdup("echo");
	else if (!ft_strcmp(name, "export"))
		*r = ft_strdup("export");
	else if (!ft_strcmp(name, "unset"))
		*r = ft_strdup("unset");
	else if (!ft_strcmp(name, "exit"))
		*r = ft_strdup("exit");
	return (*r);
}

char	*ft_find_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*r;
	char	*path_str;
	char	**path_array;
	char	*temp;

	if (access(cmd, X_OK) != -1)
		return (ft_strdup(cmd));
	if (is_built_in(cmd, &r))
		return (r);
	path_str = ft_n_find_on_array(env, "PATH", 4);
	if (!path_str)
		return (NULL);
	path_array = ft_split(path_str, ':');
	temp = path_array[0];
	path_array[0] = ft_strdup(path_array[0] + 5);
	i = (free(temp), r = NULL, 0);
	while (path_array[i] && !r)
	{
		temp = ft_multi_strjoin("%s/%s", path_array[i], cmd);
		if (access(temp, F_OK) != -1)
			r = ft_strdup(temp);
		i = (free(temp), i + 1);
	}
	return (ft_free_array(path_array), r);
}
