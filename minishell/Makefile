# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gneto-co <gneto-co@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/04/24 15:59:06 by gneto-co         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
GREEN = \033[32m
NC = \033[0m
ORANGE = \033[31m\033[33m
PECKED = ----------

#--------------------------------------------------------------------------------
#-----------------------------LIBFT SOURCE FILES---------------------------------
#--------------------------------------------------------------------------------

LIBFT_PATH = ./libft

LIBFT = $(LIBFT_PATH)/libft.a

$(LIBFT):
	@$(MAKE) -C $(LIBFT_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#----------------------------PROJECT SOURCE FILES--------------------------------
#--------------------------------------------------------------------------------


PROJECT_PATH = ./$(NAME)_files

PROJECT = $(PROJECT_PATH)/$(NAME).a

$(PROJECT):
	@$(MAKE) -C $(PROJECT_PATH) --no-print-directory


#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC = cc
OBJ = $(PROJECT) $(LIBFT)
CFLAGS = -Wall -Wextra -Werror -g -I$(LIBFT_PATH) -I$(PROJECT_PATH)

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------

.DEFAULT_GOAL := all

all: $(NAME)


$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(NAME)
	@clear
	@echo "$(GREEN)\n$(PECKED) $(NAME) compiled and ready! $(PECKED)$(NC)"

clean:
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) clean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) clean --no-print-directory
	@clear
	@echo "$(ORANGE)\n$(PECKED) program objects cleaned $(PECKED)$(NC)"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_PATH) fclean --no-print-directory
	@$(MAKE) -C $(PROJECT_PATH) fclean --no-print-directory
	@clear
	@echo "$(ORANGE)\n$(PECKED) program name and objects cleaned $(PECKED)$(NC)"
	
re: fclean all
