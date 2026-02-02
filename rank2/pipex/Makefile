# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/18 17:49:39 by davigome          #+#    #+#              #
#    Updated: 2024/12/30 16:02:38 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
#BONUS_NAME = pipex_bonus

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
SRC_BONUS_DIR	= ./sources_bonus
OBJ_DIR			= ./obj
OBJ_BONUS_DIR	= ./obj_bonus

SRC_FILES		= pipex.c \
					ft_check.c \
					ft_check_2.c \
					ft_frees.c \

SRC_BONUS_FILES = 

OBJS				= $(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))
OBJS_BONUS			= $(addprefix $(OBJ_BONUS_DIR)/, $(SRC_BONUS_FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJ_BONUS_DIR)/%.o: $(SRC_BONUS_DIR)/%.c
	@mkdir -p $(OBJ_BONUS_DIR)
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(LIBFT)/libft.a  $(OBJS)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS)
	@echo "$(GREEN)Executable for pipex launched successfully!$(RESET)"

$(BONUS_NAME): $(LIBFT)/libft.a   $(OBJS_BONUS)
	@$(CC) $(CFLAGS) -o $(BONUS_NAME) $(OBJS_BONUS) $(LIBS)
	@echo "$(GREEN)Bonus for pipex_bonus launched successfully!$(RESET)"

$(LIBFT)/libft.a:
	@$(MAKE) -C $(LIBFT)

all:$(NAME)

bonus: $(BONUS_NAME)

clean:
	@$(MAKE) -C $(LIBFT) clean
	@$(RM) -r $(OBJ_DIR) $(OBJ_BONUS_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT) fclean
	@$(RM) $(NAME) $(BONUS_NAME)

re: fclean all

.PHONY: all clean fclean re