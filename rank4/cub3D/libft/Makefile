# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: davigome <davigome@studen.42malaga.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/26 23:10:09 by davigome          #+#    #+#              #
#    Updated: 2024/12/30 15:58:42 by davigome         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = gcc
CFLAGS = -Wall -Wextra -Werror
 
SRC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
 ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c\
 ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c\
 ft_memcmp.c ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c\
ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
ft_putendl_fd.c ft_putnbr_fd.c \
ft_free_matrix.c ft_cpy_int_list.c 

#Bonus section for lbft project 
SRC += ft_lstnew_bonus.c ft_lstadd_front_bonus.c ft_lstsize_bonus.c ft_lstlast_bonus.c\
 ft_lstadd_back_bonus.c ft_lstdelone_bonus.c ft_lstclear_bonus.c\
ft_lstiter_bonus.c ft_lstmap_bonus.c

#Files for printf project
SRC += ft_printf.c ft_putchar.c ft_putstring.c ft_putnumbr_signed.c ft_putpointer.c ft_putunsigned.c\
ft_puthexadecimal.c

#Files for get_next_line project
SRC += get_next_line_bonus.c get_next_line_utils_bonus.c

OBJ = $(SRC:.c=.o)

all: $(NAME)
$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)

%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	
clean: 
	@rm -rf $(OBJ) $(BONUS_OBJS)

fclean: clean
	@rm -rf $(NAME)

re: fclean all