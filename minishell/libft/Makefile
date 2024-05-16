# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:51:25 by gneto-co          #+#    #+#              #
#    Updated: 2024/05/16 17:56:17 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CONVERSION_FUNCTIONS = $(addprefix conversion_functions/, $(addsuffix .c, \
ft_atoi \
ft_itoa \
))

LIST_FUNCTIONS = $(addprefix list_functions/, $(addsuffix .c, \
ft_lstnew \
ft_lstadd_front \
ft_lstsize \
ft_lstlast \
ft_lstadd_back \
ft_lstdelone \
ft_lstclear \
ft_lstiter \
ft_lstmap \
ft_lstdup \
))

MATH_FUNCTIONS = $(addprefix math_functions/, $(addsuffix .c, \
ft_numlen \
ft_numlen_base \
op_power_of \
op_not_zero \
))

MEMORY_FUNCTIONS = $(addprefix memory_functions/, $(addsuffix .c, \
ft_memset \
ft_bzero \
ft_memcpy \
ft_memmove \
ft_memchr \
ft_memcmp \
ft_calloc \
ft_realloc \
var_size \
))

PRINT_FUNCTIONS = $(addprefix print_functions/, $(addsuffix .c, \
ft_putchar_fd \
ft_putstr_fd \
ft_putendl_fd \
ft_putnbr_fd \
ft_putnbr \
ft_putnbr_base \
ft_putchar \
ft_putstr \
ft_putstr_newline \
ft_put_unsigned_nbr \
ft_putpt \
$(addprefix ft_printf/, \
	ft_printf \
	ft_print_type \
	ft_print_type2 \
	) \
ft_print_array \
))

READ_FUNCTIONS = $(addprefix read_functions/, $(addsuffix .c, \
$(addprefix get_next_line/, \
	get_next_line \
	get_next_line_utils \
	) \
ft_filelen \
ft_get_folder_name \
ft_get_path \
ft_get_system_var \
))

STRING_FUNCTIONS = $(addprefix string_functions/, $(addsuffix .c, \
ft_strlen \
ft_strlcpy \
ft_strlcat \
ft_toupper \
ft_tolower \
ft_strchr \
ft_strrchr \
ft_strncmp \
ft_find_on_array \
ft_strnstr \
ft_split \
ft_strdup \
ft_substr \
ft_strjoin \
ft_strtrim \
ft_strmapi \
ft_striteri \
ft_multi_strjoin \
ft_free_array \
ft_char_dup \
))

VERIFICATION_FUNCTIONS = $(addprefix verification_functions/, $(addsuffix .c, \
ft_isalpha \
ft_isdigit \
ft_isalnum \
ft_isascii \
ft_isprint \
ft_nb_already_exist \
))

SOURCES = \
$(CONVERSION_FUNCTIONS) \
$(LIST_FUNCTIONS) \
$(MATH_FUNCTIONS) \
$(MEMORY_FUNCTIONS) \
$(PRINT_FUNCTIONS) \
$(READ_FUNCTIONS) \
$(STRING_FUNCTIONS) \
$(VERIFICATION_FUNCTIONS) \

OBJECTS = $(SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJECTS)
	@ar rcs $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all
