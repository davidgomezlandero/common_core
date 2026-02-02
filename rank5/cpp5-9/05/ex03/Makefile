# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/16 18:14:56 by davigome          #+#    #+#              #
#    Updated: 2025/06/15 18:47:29 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = Bureaucrat

CC = c++ 
CFLAGS = -Wall -Wextra -Werror -std=c++98
HEADERS = Bureaucrat.hpp AForm.hpp RobotomyRequestForm.hpp PresidentialPardonForm.hpp ShrubberyCreationForm.hpp Intern.hpp

# Colores
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

SRC_FILES = main.cpp\
			Bureaucrat.cpp\
			AForm.cpp\
			RobotomyRequestForm.cpp\
			PresidentialPardonForm.cpp\
			ShrubberyCreationForm.cpp\
			Intern.cpp\

OBJ_DIR = ./obj
OBJS = $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.cpp=.o))

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADERS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Executable for Bureaucrat compiled successfully!$(RESET)"

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
