/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/25 11:35:40 by yadereve         ###   ########.fr       */
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
# include <limits.h>
# include <dirent.h>
# include <stdbool.h>

// special char
# define SPECIAL_CHAR "|<>$\'\""

typedef struct s_data
{
	bool	error;
	bool	exit;
	int		exit_code;
	char 	**env;
}			t_data;

// minishell_files
int			ft_error(int nb);
//  front end
//   ft_token_split
char		**ft_token_split(char *str, t_data *data, char **env);
char		*get_next_text(char *str, int *ii, int mod);
char		*special_char_treatment(char *str, int *ii, char **env);
char		**split_str(char **array, int *str_nb, char **new_str);

// back_end
void		ft_ls(t_data *data);
void		ft_cd(char **args, t_data *data);
void		ft_exit(char **args, t_data *data);
void		ft_pwd(t_data *data);
void		ft_echo(char **args, t_data *data);
void		ft_export(char **args, t_data *data);
void		ft_unset(char **args, t_data *data);
void		ft_env(char **env, t_data *data);
void 		ft_execute(char **args, t_data *data);
/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif
