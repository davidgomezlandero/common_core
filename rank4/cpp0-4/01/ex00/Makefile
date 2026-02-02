# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 18:14:56 by davigome          #+#    #+#              #
#    Updated: 2025/05/23 18:52:09 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Zombie

CC = c++ 
CFLAGS = -Wall -Wextra -Werror -std=c++98
HEADERS = Zombie.hpp

# Colores
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

SRC_FILES = main.cpp\
			Zombie.cpp\
			randomChump.cpp\
			newZombie.cpp\
			
OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Executable for Zombie compiled successfully!$(RESET)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
