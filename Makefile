# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sfranc <sfranc@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/03/13 13:03:38 by sfranc            #+#    #+#              #
#    Updated: 2017/07/31 15:34:14 by sfranc           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = 21sh
SRCS_PATH = srcs
OBJS_PATH = objs
SRCS = 	$(addprefix $(SRCS_PATH)/, main.c\
		read/term.c \
		read/read_line.c \
		read/prompt.c \
		read/clear.c \
		read/cursor_moves.c \
		read/move_commands.c \
		read/goto.c \
		read/buffer.c \
		read/copy_cut.c \
		read/interpret.c \
		lexer/list_lexer.c \
		lexer/tokenize.c \
		lexer/get_word.c \
		lexer/get_operator.c \
		lexer/redirect.c \
		lexer/quotes.c \
		parser/parse_command.c \
		parser/syntax_error.c \
		parser/read_again.c)
OBJS =  $(SRCS:$(SRCS_PATH)/%.c=$(OBJS_PATH)/%.o)
INCLUDES = includes libft/includes
LIB = $(LIB_PATH)/libft.a
LIB_PATH = libft
LIB_TERMCAP = -ltermcap
CC = gcc
FLAGS = -Wall -Wextra -Werror
GREEN = \033[01;32m
YELLOW = \033[01;33m
CYAN = \033[01;36m
RESET = \033[00m

all: $(NAME)

$(NAME): $(LIB) $(OBJS)
	@$(CC) $(FLAGS) -o $@ $^ $(LIB_TERMCAP)
	@echo "$(GREEN)$@ : compilation OK$(RESET)"

$(LIB):
	@make -C $(LIB_PATH)
	@echo "$(GREEN)libft : compilation OK$(RESET)"

$(OBJS_PATH)/%.o: $(SRCS_PATH)/%.c $(INCLUDES)
	@mkdir -p $(OBJS_PATH)/read
	@mkdir -p $(OBJS_PATH)/lexer
	@mkdir -p $(OBJS_PATH)/parser
	@$(CC) $(FLAGS) -o $@ -c $< $(addprefix -I , $(INCLUDES))
	@echo "$@ : $(YELLOW)OK$(RESET)"

clean:
	@make clean -C $(LIB_PATH)
	@echo "clean $(LIB_PATH)/objs : $(CYAN)clean$(RESET)"
	@rm -f $(OBJS)
	@echo "clean $(OBJS): $(CYAN)clean$(RESET)"

fclean: clean
	@make fclean -C $(LIB_PATH)
	@echo "clean $(LIB) : $(CYAN)clean$(RESET)"
	@rm -f $(NAME)
	@echo "clean $(NAME) : $(CYAN)clean$(RESET)"

re: fclean all

.PHONY: clean fclean re
