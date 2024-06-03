# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yadereve <yadereve@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/15 10:09:55 by gabriel           #+#    #+#              #
#    Updated: 2024/06/03 09:04:50 by yadereve         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME				=	minishell
GREEN				=	\033[32m
NC					=	\033[0m
ORANGE				=	\033[31m\033[33m
BLUE				=	\033[1;34m
PECKED				=	----------

#--------------------------------------------------------------------------------
#--------------------------COMPILATION SPECIFICATIONS----------------------------
#--------------------------------------------------------------------------------
# -fsanitize=address

CC					=	cc
CFLAGS				=	-Wall -Wextra -Werror -g3 -fsanitize=address
LDFLAGS				=	-L/opt/homebrew/opt/readline/lib -lreadline
RM					=	rm -rf
CFLAGS 				+= -I/opt/homebrew/opt/readline/include

#--------------------------------------------------------------------------------
#----------------------------PROJECT SOURCE FILES--------------------------------
#--------------------------------------------------------------------------------
SRC_DIR				=	minishell_files
SRC					=	$(addprefix $(SRC_DIR)/, $(SRCPROJECT_SOURCES))
SRCPROJECT_SOURCES	=	$(addsuffix .c, \
						\
						\
						main \
						ft_error \
						\
						\
						front_end/readline_loop/ft_readline_loop \
						front_end/readline_loop/handle_signals \
						\
						front_end/token_split/ft_token_split \
						front_end/token_split/special_char \
						front_end/token_split/get_next_text \
						\
						front_end/cmd_table/create_cmd_table \
						front_end/cmd_table/get_name_args \
						front_end/cmd_table/ft_print_table \
						front_end/cmd_table/ft_free_table \
						\
						\
						back_end/ft_execute/ft_execute \
						back_end/ft_execute/ex_cmd \
						back_end/ft_execute/ex_great \
						back_end/ft_execute/ex_greatgreat \
						back_end/ft_execute/ex_less \
						back_end/ft_execute/ex_lessless \
						back_end/ft_execute/ex_pipe \
						back_end/ft_execute/ft_find_cmd_path \
						\
						back_end/built_in/ft_cd \
						back_end/built_in/ft_echo \
						back_end/built_in/ft_env \
						back_end/built_in/ft_exit \
						back_end/built_in/ft_pwd \
						back_end/built_in/ft_unset \
						back_end/built_in/ft_export \
						back_end/built_in/ft_export_2 \
						back_end/built_in/ft_export_3 \
)

SRC_DIR = minishell_files

OBJ_DIR				=	objects
OBJ					=	$(addprefix $(OBJ_DIR)/,$(SRC:$(SRC_DIR)/%.c=%.o))

#--------------------------------------------------------------------------------
#-----------------------------LIBFT FILES----------------------------------------
#--------------------------------------------------------------------------------

LIBFT				=	./libft/libft.a

#--------------------------------------------------------------------------------
#---------------------------------MAKEFILE RULES---------------------------------
#--------------------------------------------------------------------------------
# .DEFAULT_GOAL := all

all: $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

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
