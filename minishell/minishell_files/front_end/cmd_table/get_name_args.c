/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_name_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/17 11:12:43 by gneto-co          #+#    #+#             */
/*   Updated: 2024/06/24 15:53:10 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	new_line_initialize_data(t_table_data *new_line)
{
	new_line->name = NULL;
	new_line->args = malloc(sizeof(char *));
	new_line->args[0] = NULL;
	new_line->args_amount = 0;
	new_line->in_fd = 0;
	new_line->out_fd = 0;
	new_line->path = NULL;
	new_line->pid = 0;
}

char	*ft_corr(char *str)
{
	char *temp_str;

	temp_str = NULL;
	if (ft_isdigit(str[1]))
	{
		temp_str = ft_substr(str, 2, ft_strlen(str));
		free(str);
	}
	else
		temp_str = str;
	// ft_printf("str: %s\n", str); //MARK
	// ft_printf("temp_str: %s\n", temp_str); // MARK
	return (temp_str);
}

// se for " expande tudo
static void quote_op1(t_data *data, t_table_data *new_line, char **array, int i)
{
	int j;
	int		k;
	char	*temp_str;
	char	*final_str;
	char 	*temp_var_name;
	char	**temp_split;
	
	j = 1;
	k = 0;
	temp_str = NULL;
	final_str = NULL;
	temp_var_name = NULL;
	temp_split = NULL;
	while (array[i][j])
	{
		if (array[i][j] == '$')
		{
			j++;
			temp_var_name = get_next_text(array[i], &j, 1);
			temp_str = ft_getenv(temp_var_name, data->env);
			temp_split = ft_split(temp_str, ' ');
			k = 0;
			while (temp_split[k])
			{
				final_str = ft_strjoin_free(final_str, temp_split[k]);
				k++;
			}
			free(temp_var_name);
			free(temp_str);
			ft_free_array(temp_split);
		}
		else
		{
			temp_str = get_next_text(array[i], &j, '\"');
			final_str = ft_strjoin_free(final_str, temp_str);
			free(temp_str);
		}
	}
	new_line->args = split_str(new_line->args, &new_line->args_amount,
				ft_strdup(final_str));
	free(final_str);
}

// se for $ expande só esse
static void quote_op2(t_data *data, t_table_data *new_line, char **array, int i)
{
	char	*temp_str;
	temp_str = NULL;
	
	temp_str = ft_getenv(array[i] + 1, data->env);
	new_line->args = split_str(new_line->args, &new_line->args_amount,
			ft_strdup(temp_str));
}

 // se for ' não expande nada
static void quote_op3(t_table_data *new_line, char **array, int i)
{
	new_line->args = split_str(new_line->args, &new_line->args_amount,
				ft_strdup(array[i] + 1));
}



static void	set_cmd_arg(t_data *data, t_table_data *new_line, char **array,
		int i)
{
	char	quote;
	quote = array[i][0];
	// ft_printf("name: %s\n", new_line->name); //MARK
	// ft_printf("args: %s\n", new_line->args[0]); //MARK
	
	// ft_printf("1- array[i] = %s\n", array[i]); // MARK // 1- array[i]

	if (!ft_strcmp(new_line->name, "echo") && ft_strncmp(array[i] + 1, "$", 1) == 0 /* && ft_strcmp(array[i], "$") */)
		array[i] = ft_corr(array[i]);
	
	// ft_printf("2- array[i] = %s\n", array[i]); // MARK // 2- array[i]
	
	if (quote == '\"')
		quote_op1(data, new_line, array, i);
	else if (quote == '$') 
		quote_op2(data, new_line, array, i);
	else if (quote == '\'')
		quote_op3(new_line, array, i);
	else
	{
		new_line->args = split_str(new_line->args, &new_line->args_amount,
				ft_strdup(array[i]));
	}
}

static char	*get_name(char *str, t_data *data, int t)
{
	char	*new_str;
	char	**temp_array;
	char	quote;

	quote = str[0];
	if (quote == '\'' || quote == '\"')
		str++;
	if ((ft_strncmp(str, "$", 1) == 0) && (t == CMD) && (quote != '\''))
	{
		str++;
		new_str = ft_get_system_var(str, data->env);
		if (!new_str || !ft_strchr(new_str, ' '))
		{
			return (new_str);
		}
		temp_array = ft_split(new_str, ' ');
		new_str = ft_strdup(temp_array[0]);
		ft_free_array(temp_array);
		return (new_str);
	}
	else if ((ft_strncmp(str, "$", 1) == 0) && (t != LESSLESS)
		&& (quote != '\''))
	{
		str++;
		new_str = ft_get_system_var(str, data->env);
		if (!ft_strchr(new_str, ' '))
			return (new_str);
		data->error = true;
		ft_error(5, --str);
		return (NULL);
	}
	else
		return (ft_strdup(str));
}



/*
 * 	function : will transform tokens into a command
 *
 * 	· first token : name
 * 	· next tokens : args
 */
static void	cmd_manager(t_data *data, t_table_data *new_line, char **array,
		int *ii)
{
	int	i;

	i = *ii;
	i--;
	if (new_line->type == CMD)
		new_line->name = get_name(array[i], data, CMD);
	// new_line->args = split_str(new_line->args, &new_line->args_amount,
	// 		ft_strdup(new_line->name));
	// 	set_cmd_arg(data, new_line, array, i);
	while (get_line_type(array, i) == CMD)
	{
		// ft_print_array_tester(new_line->args); // MARK
		set_cmd_arg(data, new_line, array, i);
		i++;
	}
	*ii = i;
}

/*
 * 	function : will transform tokens into a redirection
 *
 * 	· if next token isn't a normal string : error
 * 	· if it is put it as file name
 */
static void	redirection_manager(t_data *data, t_table_data *new_line,
		char **array, int *ii)
{
	int		i;
	char	*type;
	int		t;

	t = new_line->type;
	i = *ii;
	type = NULL;
	if (get_line_type(array, i) != 1)
	{
		if (t == LESS)
			type = ft_strdup("<");
		if (t == LESSLESS)
			type = ft_strdup("<<");
		if (t == GREAT)
			type = ft_strdup(">");
		if (t == GREATGREAT)
			type = ft_strdup(">>");
		data->error = true;
		ft_error(2, type);
		free(type);
		return ;
	}
	new_line->name = get_name(array[i++], data, t);
	*ii = i;
}

/*
 * 	function : will see tokens and put correspondent name and
 * 	args on new_line
 *
 * 	if <, <<, > or >> : get the file name
 * 	if | : do nothing
 * 	if cmd : look for name and args
 *
 * 	· initialize vars
 * 	· if is a redirection : redirection_manager
 * 	· if is a command : cmd_manager
 */
t_table_data	*get_name_args(t_table_data *new_line, char **array, int *ii,
		t_data *data)
{
	int	i;
	int	t;

	t = new_line->type;
	i = *ii + 1;
	new_line_initialize_data(new_line);
	if (t == LESS || t == LESSLESS || t == GREAT || t == GREATGREAT)
		redirection_manager(data, new_line, array, &i);
	else if (t == CMD)
	{
		cmd_manager(data, new_line, array, &i);
		if (data->error == true)
			return (new_line);
	}
	*ii = i;
	return (new_line);
}
