/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/31 17:53:15 by gneto-co         ###   ########.fr       */
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
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <limits.h>
# include <dirent.h>
# include <stdbool.h>

// special char
# define SPECIAL_CHAR "|<>$\'\""

// table_type
# define CMD 1
# define PIPE 2
# define LESS 3
# define GREAT 4
# define LESSLESS 5
# define GREATGREAT 6

// lessless temp file name
# define LESSLESS_TEMP_FILE ".lessless"

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
	bool			infile_error;
	t_table_data	**table;
	char			**env;
	int				in_fd;
	int				out_fd;
	int				process_status;
	bool			exit;
	int				exit_code;
}			t_data;

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
void				handle_sigint(int sig);
void				handle_sigquit(int sig);
char				*get_prompt_text(void);

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

/*  cmd  */
char				*ft_find_cmd_path(char *cmd, char **env);
void				ft_ls(t_data *data);
void				ft_cd(char **args, t_data *data);
void				ft_exit(char **args, t_data *data);
void				ft_pwd(t_data *data);
void				ft_echo(char **args, t_data *data);
void				ft_export(char **args, t_data *data);
void				ft_unset(char **args, t_data *data);
void				ft_env(char **env, t_data *data);
void				ft_array_n_delone(char ***array, int index);
void				ft_swap(char **a, char **b);
char				**ft_sort_env(char **env);
void				ft_print_export(char **env);
bool				is_valid_identifier(const char *str);
char				*get_env_var(char *str);
int					find_var(char **env, char *var);
void				update_env_str(char **str, char *new_var);
char				**ft_create_env(char *new_var);
void				free_array(char ***array);
void				add_new_arg(char ***env, char *new_var);
void				update_env(char ***env, char *arg);
void				cd_update_env(t_data *data);
void				ft_chdir(char *path, t_data *data);
void				cd_dir(char **args, t_data *data);

/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif
