# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/05/10 11:47:11 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
GREEN = \033[32m
NC = \033[0m
ORANGE = \033[31m\033[33m
BLUE = \033[1;34m
PECKED = ----------

#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LDFLAGS = -lreadline
RM = rm -rf

#--------------------------------------------------------------------------------
#----------------------------PROJECT SOURCE FILES--------------------------------
#--------------------------------------------------------------------------------

SRC_DIR = minishell_files
SRC = $(addprefix $(SRC_DIR)/, $(SRCPROJECT_SOURCES))
SRCPROJECT_SOURCES = $(addsuffix .c, \
main \
ft_error \
\
$(addprefix \
back_end/, \
	example_file1 \
	mini_command \
) \
$(addprefix \
front_end/, \
	$(addprefix ft_token_split, \
	/ft_token_split \
	/special_char \
	) \
) \
)

OBJ_DIR = objects
OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:$(SRC_DIR)/%.c=%.o))

#--------------------------------------------------------------------------------
#-----------------------------LIBFT FILES----------------------------------------
#--------------------------------------------------------------------------------

LIBFT = ./libft/libft.a

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------
# .DEFAULT_GOAL := all

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@ $(LDFLAGS)

$(NAME): $(OBJ) $(LIBFT)
	@echo "$(BLUE)           __         __         __           __ __"
	@echo ".--------.|__|.-----.|__|.-----.|  |--.-----.|  |  |"
	@echo "|        ||  ||     ||  ||__ --||     |  -__||  |  |"
	@echo "|__|__|__||__||__|__||__||_____||__|__|_____||__|__|\n$(NC)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(LDFLAGS)
	@echo "$(GREEN)\n$(PECKED) $(NAME) compiled and ready! $(PECKED)$(NC)"

$(LIBFT):
	@$(MAKE) -C ./libft --no-print-directory

clean:
	@$(RM) $(OBJ_DIR)
	@$(MAKE) -C ./libft clean --no-print-directory
#	@clear
	@echo "$(ORANGE)\n$(PECKED) program objects cleaned $(PECKED)$(NC)"


fclean: clean
	@$(RM) $(NAME)
	@$(MAKE) -C ./libft fclean --no-print-directory
#	@clear
	@echo "$(ORANGE)\n$(PECKED) program name and objects cleaned $(PECKED)$(NC)"

re: fclean all

.PHONY: all clean fclean re
