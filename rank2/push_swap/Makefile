# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 17:49:39 by davigome          #+#    #+#              #
#    Updated: 2025/01/04 20:00:29 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = push_swap

CC = gcc -g
CFLAGS = -Wall  -Wextra -Werror
LIBFT = ./libft
INCLUDES = -I$(LIBFT)/include -Iincludes
LIBS = -L$(LIBFT) -lft

# Colores
RED = \033[31m
GREEN = \033[32m
YELLOW = \033[33m
BLUE = \033[34m
RESET = \033[0m

SRC_DIR			= ./sources
OBJ_DIR			= ./obj

SRC_FILES		= push_swap.c \
					ft_checks.c \
					ft_checks_2.c \
					ft_frees.c \
					ft_utils.c \
					ft_utils_2.c \
					ft_utils_3.c \
					ft_start.c \
					ft_start_2.c \
					ft_start_3.c \
					ft_moves.c \
					ft_moves_2.c

OBJS				= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT)/libft.a  $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)Executable for push_swap launched successfully!$(RESET)"

$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

all:$(NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re