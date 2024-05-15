/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/15 13:23:51 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* *********************************** */
/*                                     */
/*           MINISHELL HEADER          */
/*                                     */
/* *********************************** */

# include "../libft/libft.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

// int
# define INT_MAX 2147483647
# define INT_MIN -2147483648
// boll
# define bool int
# define true 1
# define false 0
// special char
# define SPECIAL_CHAR "|<>$\'\""
// table_type
# define TYPE int
# define CMD 1
# define PIPE 2
# define LESS 3
# define GREAT 4
# define LESSLESS 5
# define GREATGREAT 6

typedef struct s_data
{
	bool		error;
}				t_data;

typedef struct s_table_data
{
	TYPE		type;
	char		*name;
	char		**flags;
	int			flags_amount;
	char		**args;
	int			args_amount;
}				t_table_data;

//
// ╭─┤ minishell_files ├─
// │
int				ft_error(int nb);
// │
// ╰───┤ front end ├─
//   │
//   ╰─────┤ ft_execute ├─
//
int				ft_execute(char **array_user_input, t_data *data, char **env);
t_table_data	**create_cmd_table(char **array);
void			ft_print_table(t_table_data **table);
//   │
//   ╰─────┤ ft_readline_loop ├─
//
void			ft_readline_loop(t_data *data, char **env);
//   │
//   ╰─────┤ ft_token_split ├─
//
char			**ft_token_split(char *str, t_data *data, char **env);
char			*get_next_text(char *str, int *ii, int mod);
char			*special_char_treatment(char *str, int *ii, char **env);
char			**split_str(char **array, int *str_nb, char *new_str);
// │
// ╰───┤ back_end ├─
//
int				ft_cd(char **args);
int				ft_exit(char **args);
int				ft_pwd(char **args);
int				ft_echo(char **args);
int				ft_export(char **args);
int				ft_unset(char **args);
int				ft_env(char **args);
/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif
