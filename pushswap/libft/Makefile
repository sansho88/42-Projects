# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgriffit <tgriffit@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/04 11:56:35 by tgriffit          #+#    #+#              #
#    Updated: 2022/04/04 16:19:04 by tgriffit         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


BBLU 		=	\033[1;34m
BGREEN		=	\033[1;32m
BRED		=	\033[1;31m
BLU 		=	\033[0;34m
GRN 		=	\033[0;32m
RED 		=	\033[0;31m
RST 		=	\033[0m

NAME = libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
AR =  @ar rcs
RM = @rm -f
HEADER = ./includes/

SRCS = ft_bzero.c \
		ft_memcpy.c \
		ft_memmove.c \
		ft_strlen.c \
		ft_strlcpy.c \
		ft_strlcat.c \
		ft_strchr.c \
		ft_strrchr.c \
		ft_strnstr.c \
		ft_strncmp.c \
		ft_atoi.c \
		ft_atoll.c \
		ft_isalpha.c \
		ft_isdigit.c \
		ft_str_isdigit.c \
		ft_isInteger.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_striseq.c \
		ft_substr.c \
		ft_strjoin.c \
		ft_strtrim.c \
		ft_split.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_putnbr_fd.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h Makefile
	@echo "\033c\033[93mLibft is compiling\033[0m"
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "\033[r\033[1;32mLibft is ready now!\033[0m"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "\033[0;31mlibft clean\033[0m"

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re