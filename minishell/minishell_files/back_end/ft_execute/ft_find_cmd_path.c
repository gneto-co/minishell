/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_cmd_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 14:24:13 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 13:09:58 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char *is_built_in(char *name)
{
	if (!ft_strcmp(name, "ls"))
		return (ft_strdup("ls"));
	else if (!ft_strcmp(name, "cd"))
		return (ft_strdup("cd"));
	else if (!ft_strcmp(name, "env"))
		return (ft_strdup("env"));
	else if (!ft_strcmp(name, "pwd"))
		return (ft_strdup("pwd"));
	else if (!ft_strcmp(name, "echo"))
		return (ft_strdup("echo"));
	else if (!ft_strcmp(name, "export"))
		return (ft_strdup("export"));
	else if (!ft_strcmp(name, "unset"))
		return (ft_strdup("unset"));
	else if (!ft_strcmp(name, "exit"))
		return (ft_strdup("exit"));
	return (NULL);
}

char	*ft_find_cmd_path(char *cmd, char **env)
{
	int		i;
	char	*r;
	char	*path_str;
	char	**path_array;
	char	*temp;

	r = is_built_in(cmd);
	if (r)
		return (r);
	path_str = ft_n_find_on_array(env, "PATH", 4);
	path_array = ft_split(path_str, ':');
	temp = path_array[0];
	path_array[0] = ft_strdup(path_array[0] + 5);
	free(temp);
	i = 0;
	r = NULL;
	while (path_array[i] && !r)
	{
		temp = ft_multi_strjoin("%s/%s", path_array[i], cmd);
		if (access(temp, F_OK) != -1)
			r = ft_strdup(temp);
		free(temp);
		i++;
	}
	ft_free_array(path_array);
	return (r);
}
