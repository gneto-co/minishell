/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/17 18:59:45 by gneto-co         ###   ########.fr       */
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

// special char
# define SPECIAL_CHAR "|<>$\'\""

// table_type
# define CMD 1
# define PIPE 2
# define LESS 3
# define GREAT 4
# define LESSLESS 5
# define GREATGREAT 6

typedef struct s_table_data
{
	int				type;
	char			*name;

	int				pipe_fd[2];

	char			**args;
	int				args_amount;
	int				in_fd;
	int				out_fd;
	char			*path;
	int				pid;
}					t_table_data;

typedef struct s_data
{
	bool			error;
	t_table_data	**table;
	char			**env;
	int				in_fd;
	int				out_fd;
}					t_data;

/* *********************************** */
/*                                     */
/*           MINISHELL FILES           */
/*                                     */
/* *********************************** */

int					ft_error(int nb, char *str);

/*                   */
/*     front_end     */
/*                   */

/*  ft_readline_loop  */
void				ft_readline_loop(t_data *data);

/*  ft_token_split  */
char				**ft_token_split(char *str, t_data *data);
char				*get_next_text(char *str, int *ii, int mod);
char				*special_char_manager(char *str, int *ii, t_data *data);
char				**split_str(char **array, int *str_nb, char *new_str);
char				*get_real_next_text(char *str, int *ii, t_data *data);

/*  ft_table  */
t_table_data		**create_cmd_table(char **array, t_data *data);

t_table_data		*get_name_args(t_table_data *new_line, char **array,
						int *ii, t_data *data);
int					get_line_type(char **array, int i);
void				ft_print_table(t_table_data **table);
void				ft_free_table(t_table_data **table);

/*                    */
/*      back_end      */
/*                    */

/*  ft_execute  */
int					ft_execute(t_data *data);
void				ex_cmd(t_data *data, int i);
void				ex_pipe(t_data *data, int i);
void				ex_less(t_data *data, int i);
void				ex_great(t_data *data, int i);
void				ex_lessless(t_data *data, int i);
void				ex_greatgreat(t_data *data, int i);
char				*ft_find_cmd_path(char *cmd, char **env);

/*  commands  */
int					ft_cd(char **args);
int					ft_exit(char **args);
int					ft_pwd(char **args);
int					ft_echo(char **args);
int					ft_export(char **args);
int					ft_unset(char **args);
int					ft_env(char **args);

/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif
