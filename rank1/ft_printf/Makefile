# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/30 23:11:57 by davigome          #+#    #+#              #
#    Updated: 2024/08/12 16:50:21 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = cc
AR = ar rcs
RM = rm -rf
CP = cp
#-fPIC is used to ensure that the shared code is position-independent, meaning 
#it can be loaded anywhere in memory without the need to modify the .text section.
CFLAGS = -Wall -Wextra -Werror -fPIC 

LIBFT = ./libft/libft.a
LIBFTDIR = ./libft

FUNCDIR = ./functions
PRINTF_SRCS = ft_printf.c ft_putchar.c ft_putstring.c ft_putnumbr_signed.c ft_putpointer.c ft_putunsigned.c\
ft_puthexadecimal.c
OBJS = $(PRINTF_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(LIBFT) $(OBJS)
	$(CP) $(LIBFT) $(NAME)
	@$(AR) $(NAME) $(OBJS)

$(LIBFT): $(LIBFTDIR)
	@$(MAKE) -C $(LIBFTDIR)

%.o: $(FUNCDIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I ../libft

clean:
	@$(MAKE) clean -C $(LIBFTDIR)
	@$(RM) $(OBJS)

fclean: clean
	@$(MAKE) fclean -C $(LIBFTDIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re 