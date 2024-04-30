/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 17:38:09 by gneto-co          #+#    #+#             */
/*   Updated: 2024/01/12 18:01:28 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <unistd.h>
# include <fcntl.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

int long	ft_strlen(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_str_char_join(char *str, char c);
char		*ft_strdup(const char *src);
static char	*sort(char *str, char c, va_list args);
char		*ft_multi_strjoin(const char *source, ...);
char		*ft_itoa(int n);
char	    *get_next_line(int fd);
int         ft_atoi(const char *nptr);

#endif
