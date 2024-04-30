# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/09 10:51:25 by gneto-co          #+#    #+#              #
#    Updated: 2024/04/30 17:16:19 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

PROJECT_SOURCES = $(addsuffix .c, \
main \
\
$(addprefix \
back_end/, \
	example_file1 \
	example_file2 \
) \
$(addprefix \
front_end/, \
	$(addprefix ft_token_split, \
	/ft_token_split \
	/special_char \
	) \
) \
)

SOURCES = $(PROJECT_SOURCES)
	
OBJECTS = $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS) 
	@ar rcs $(NAME) $(OBJECTS)

clean:
	@rm -f $(OBJECTS)

fclean: clean
	@rm -f $(NAME)

re: fclean all