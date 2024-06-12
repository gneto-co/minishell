/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 13:20:47 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/12 21:30:31 by yadereve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_is_dollar(char *str, t_data *data)
{
	int		start;
	int		i;
	char	*name_var;
	char	*env_var;

	i = 0;
	start = i;
	name_var = NULL;
	env_var = NULL;
	ft_printf("i_1 = %d\n", i); // MARK
	while (str[(i)])
	{
		if (ft_isalpha(str[(i)]) || str[(i)] == '_')
			break ;
		(i)++;
	}
	ft_printf("i_2 = %d\n", i);
	name_var = ft_substr(str, start, (i));
	ft_printf("name_var = %s\n", name_var); // MARK
	if (name_var)
	{
		env_var = ft_getenv(name_var, data->env);
		ft_putout(env_var, data);
		free(name_var);
		free(env_var);
	}
	return (i);
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
	data->process_status = 0;
	while (!ft_strcmp(args[i], "-n"))
	{
		flag = true;
		i++;
	}
	while (args[i])
	{
		if (!ft_strchr(args[i], '$'))
			i = ft_is_dollar(args[i], i, data); // FIXME
		ft_putout(args[i], data);
		if (args[++i])
			ft_putout(" ", data);
	}
	if (flag == false)
		ft_putout("\n", data);
}

/**
 * ./minishell

minishell
> echo $USER
i_1 = 1
i_2 = 1
name_var = a
yadereve

minishell
>
exit

*/
