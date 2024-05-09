/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:22:31 by gneto-co          #+#    #+#             */
/*   Updated: 2024/05/09 15:09:02 by gneto-co         ###   ########.fr       */
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

// int
# define INT_MAX 2147483647
# define INT_MIN -2147483648
// boll
# define bool int
# define true 1
# define false 0
// special char
# define SPECIAL_CHAR "|<>$\'\""

typedef struct s_data
{
	bool	error;
}		t_data;

// minishell_files
int		ft_error(int nb);
//  front end
//   ft_token_split
char	**ft_token_split(char *str, t_data *data, char **env);
char	*get_next_text(char *str, int *ii, int mod);
char	*special_char_treatment(char *str, int *ii, char **env);
char	**split_str(char **array, int *str_nb, char **new_str);

/* *********************************** */
/*                                     */
/*                 END                 */
/*                                     */
/* *********************************** */

#endif