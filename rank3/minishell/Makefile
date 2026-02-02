PROJECT 	:= minishell 
CC 			:= gcc

CFLAGS		:= -Wextra -Wall -Werror -g #-fsanitize=address
LDFLAGS     := -lreadline

LIBFT		:= ./lib/libft/libft.a
INCLUDE 	:= -I ./include

SRC_DIR 	:= src
SRC			:=	main.c \
				ms_env.c \
				ms_utils.c \
				ms_utils_2.c \
				ms_utils_3.c \
				ms_get_exec.c \
				ms_prompt.c \
				ms_parse.c \
				ms_builtin.c \
				ms_builtin_funcs.c \
				ms_builtin_funcs_2.c \
				ms_split_out.c \
				ms_split_out_2.c \
				ms_nodes.c \
				ms_here_doc.c \
				ms_params.c \
				ms_cmd.c \
				ms_fork_check.c \
				ms_child_builtin.c \

				

OBJ_DIR 	:= obj
OBJ 		:= $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
BIN_DIR		:= bin
NAME		:= $(BIN_DIR)/$(PROJECT)

# Libft

LIBFT_REPO = https://github.com/Thedeivi10/libft.git
LIBFT_DIR = libft
LIBFT_LIB = $(LIBFT_DIR)/libft.a

RED     := \033[31m
GREEN   := \033[32m
YELLOW  := \033[33m
BLUE 	:= \033[96m
RESET   := \033[0m

all: $(NAME)

libft:
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning $(YELLOW)libft$(RESET) repository..."; \
		git clone $(LIBFT_REPO) > /dev/null 2>&1; \
	fi
		@$(MAKE) -C $(LIBFT_DIR) > /dev/null 2>&1

$(LIBFT_LIB): libft

$(NAME): $(LIBFT_LIB) $(OBJ) | $(BIN_DIR)
	@echo "Compiling $(YELLOW)$(PROJECT)$(RESET) with $(BLUE)$(CFLAGS)$(RESET)..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT_LIB) $(LDFLAGS)
	@echo "$(GREEN)Done! ✅$(RESET)"
	@echo "$(RED)------------------------------$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean > /dev/null 2>&1

fclean: clean
	@rm -rf $(BIN_DIR)
	@$(MAKE) -C $(LIBFT_DIR) fclean > /dev/null 2>&1
	@rm -rf $(LIBFT_DIR)

re: fclean all

.PHONY: all libft clean fclean re