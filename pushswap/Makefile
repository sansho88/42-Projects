# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 11:49:49 by tgriffit          #+#    #+#              #
#    Updated: 2022/04/04 12:18:37 by tgriffit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

BBLU 		=	\033[1;34m
BGREEN		=	\033[1;32m
BRED		=	\033[1;31m
BLU 		=	\033[0;34m
GRN 		=	\033[0;32m
RED 		=	\033[0;31m
RST 		=	\033[0m
YLW			=	\033[93m

NAME := push_swap
LIBFT_PATH := libft/
LIBFT := $(LIBFT_PATH)libft.a
FLAGS := -Wall -Werror -Wextra

SRCS := radix.c \
		sort.c \
		op_utils.c \
		rotatenreverse.c \
		swapush.c \
		utils.c

OBJS = $(SRCS:.c=.o)

all: libftmake $(NAME)

%.o:%.c pushswap.h Makefile
	$(CC) $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
		$(CC) $(FLAGS) $(LIBFT) $(OBJS) -o $(NAME)
		@echo "\033[1;32mpush_swap is ready."
		@echo "\033[0mYou can use it like: \n\033[7m./push_swap \"0 42 128 84 -42\" "
		@echo "\033[0m or \033[7m./push_swap 0 42 -128 \033[0m"

$(LIBFT): libftmake

libftmake:
		@make -C $(LIBFT_PATH)

libftclean:
		make fclean -C $(LIBFT_PATH)

clean:
		rm -f $(OBJS)
		@echo "\033[1;31mFiles for compilation deleted\033[0m"

fclean: clean libftclean
		rm -f $(NAME)
		@echo "\033[1;31mpush_swap deleted\033[0m"

re: clean all

.PHONY: all clean fclean re libftmake libftclean
.SILENT:

