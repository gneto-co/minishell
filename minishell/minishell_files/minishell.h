/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 18:46:50 by yadereve         ###   ########.fr       */
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
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include <sys/types.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648
# define SPECIAL_CHAR "|<>$\'\""

typedef struct s_data
{
	int	test;
}		t_data;

void	lsh_loop(void);
// front end
//  ft_token_split
char	**ft_token_split(char *str, char **env);
char	**special_char_treatment(char **array, int *str_nb, char **str,
			char **env);
char	**split_str(char **array, int *str_nb, char **new_str);

// back_end
int	ft_cd(char **args);
int	ft_exit(char **args);
int	ft_pwd(char **args);
int	ft_echo(char **args);
int	ft_export(char **args);
int	ft_unset(char **args);
int	ft_env(char **args);
/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif
