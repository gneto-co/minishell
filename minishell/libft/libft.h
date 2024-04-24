/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 10:30:24 by gneto-co          #+#    #+#             */
/*   Updated: 2024/04/09 09:48:06 by gneto-co         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <fcntl.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define INT_MAX 2147483647
# define INT_MIN -2147483648

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

// conversion_funtions
int					ft_atoi(const char *nptr);
char				*ft_itoa(int nbr);
int					ft_atoi_base(const char *str, int str_base);

// list_functions
t_list				*ft_lstnew(void *content);
void				ft_lstadd_front(t_list **lst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **lst, t_list *new);
void				ft_lstdelone(t_list *lst, void (*del)(void *));
void				ft_lstclear(t_list **lst, void (*del)(void *));
void				ft_lstiter(t_list *lst, void (*f)(void *));
t_list				*ft_lstmap(t_list *lst, void *(*f)(void *),
						void (*del)(void *));
t_list				*ft_lst_second_last(t_list *lst);
t_list				*ft_lstdup(t_list *lst, void (*del)(void *),
						void *(*dupcontent)(void *));

// math_funtions
int					op_square(int number);
int					op_power_of(int base, int exponent);
int					ft_numlen(int long nbr);
int					ft_numlen_base(int nbr, int base);
int					op_not_zero(int nb);

// memory_funtions
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);

// print_functions
void				ft_putchar_fd(char c, int fd);
void				ft_putstr_fd(char *s, int fd);
void				ft_putendl_fd(char *s, int fd);
void				ft_putnbr_fd(int n, int fd);
void				ft_putnbr(int n);
int					ft_putnbr_base(unsigned int nbr, char *base, int total);
void				ft_putchar(char c);
void				ft_putstr(char *s);
void				ft_putstr_newline(char *s);
int					ft_put_unsigned_nbr(unsigned int n, int total);
int					ft_putpt(unsigned long int nbr, char *base, int total);
int					ft_printf(const char *str, ...);

// read_funcitons
char				*get_next_line(int fd);
size_t				ft_filelen(char *file_name);

// string_functions
int long			ft_strlen(const char *str);
int long			ft_arraylen(char **str);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strchr(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
char				*ft_find_on_array(char **array, char *str);
char				*ft_n_find_on_array(char **array, char *str, int n);
int					ft_strcmp(char *s1, char *s2);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
char				*ft_strnstr(const char *big, const char *little,
						size_t len);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *s1, char const *set);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
char				*ft_strdup(const char *src);
char				**ft_split(char const *str, char c);
char				*ft_multi_strjoin(const char *source, ...);
char				*ft_str_char_join(char *str, char c);
void				ft_free_array(char **array);
void				ft_free_array_content(char **array);

// verification_functions
int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
int					ft_nb_already_exist(int *nb_list, int nb, size_t size);

#endif