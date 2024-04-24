# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:51:25 by gneto-co          #+#    #+#              #
#    Updated: 2023/10/18 13:33:08 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

LFT = libft/

SOURCES = \
	ft_printf.c ft_print_type.c ft_print_type2.c\
	
LIBFT_SOURCES = \
	$(LFT)ft_isalpha.c $(LFT)ft_isdigit.c $(LFT)ft_isalnum.c $(LFT)ft_isascii.c $(LFT)ft_isprint.c \
	$(LFT)ft_strlen.c $(LFT)ft_memset.c $(LFT)ft_bzero.c $(LFT)ft_memcpy.c $(LFT)ft_memmove.c \
	$(LFT)ft_strlcpy.c $(LFT)ft_strlcat.c $(LFT)ft_toupper.c $(LFT)ft_tolower.c $(LFT)ft_strchr.c \
	$(LFT)ft_strrchr.c $(LFT)ft_strncmp.c $(LFT)ft_memchr.c $(LFT)ft_memcmp.c $(LFT)ft_strnstr.c $(LFT)ft_atoi.c \
	$(LFT)ft_calloc.c $(LFT)ft_strdup.c $(LFT)ft_substr.c $(LFT)ft_strjoin.c $(LFT)ft_strtrim.c \
	$(LFT)ft_split.c $(LFT)ft_itoa.c $(LFT)ft_strmapi.c $(LFT)ft_striteri.c \
	$(LFT)ft_lstnew.c $(LFT)ft_lstadd_front.c $(LFT)ft_lstsize.c $(LFT)ft_lstlast.c \
	$(LFT)ft_lstadd_back.c $(LFT)ft_lstdelone.c $(LFT)ft_lstclear.c \
	$(LFT)ft_lstiter.c $(LFT)ft_lstmap.c \
	$(LFT)ft_putchar_fd.c $(LFT)ft_putstr_fd.c $(LFT)ft_putendl_fd.c $(LFT)ft_putnbr_fd.c \
	$(LFT)ft_putstr_newline.c \
	$(LFT)ft_putchar.c $(LFT)ft_numlen.c $(LFT)ft_putnbr.c $(LFT)ft_putnbr_base.c \
	$(LFT)ft_numlen_base.c $(LFT)ft_putstr.c \
	$(LFT)ft_put_unsigned_nbr.c $(LFT)ft_putpt.c
	
OBJECTS = $(SOURCES:.c=.o)

LIBFT_OBJECTS = $(LIBFT_SOURCES:.c=.o)

CC = cc

CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJECTS) $(LIBFT_OBJECTS)
	ar rcs $(NAME) $(OBJECTS) $(LIBFT_OBJECTS)

clean:
	rm -f $(OBJECTS) $(LIBFT_OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all