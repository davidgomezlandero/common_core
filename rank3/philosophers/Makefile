# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/04 19:57:32 by davigome          #+#    #+#              #
#    Updated: 2025/05/19 19:47:52 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CC = gcc -pthread
CFLAGS = -Wall  -Wextra -Werror
HELGRIND = valgrind --tool=helgrind ./philo 180 810 200 200 7
VALGRIND = valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./philo 3 810 200 200


# Colores
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

SRC_DIR			= ./sources
OBJ_DIR			= ./obj

SRC_FILES		= philosophers.c \
					ft_check.c \
					utils.c \
					forks.c \
					philos.c \
					actions.c \
					ft_dead.c \

OBJS				= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	@echo "$(GREEN)Executable for philo launched successfully!$(RESET)"

all:$(NAME)

valgrind:
	$(VALGRIND)

helgrind:
	$(HELGRIND)

clean:
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re