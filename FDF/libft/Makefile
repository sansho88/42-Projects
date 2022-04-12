# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/10 17:13:35 by tgriffit          #+#    #+#             #
#   Updated: 202#   Updated: 2022/02/18 10:57:24 by tgriffit         ###   ########.fr       #                                                              #
# ************************************************************************** #

NAME = libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
AR =  @ar rcs
RM = @rm -f
HEADER = ./includes/

SRCS = 	ft_bzero.c \
		ft_memcpy.c \
		ft_strlen.c \
		ft_strchr.c \
		ft_atoi.c \
		ft_isdigit.c \
		ft_calloc.c \
		ft_strdup.c \
		ft_strjoin.c \
		ft_split.c \
		ft_itoa.c \
		ft_putchar_fd.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c

OBJS = $(SRCS:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "Libft is ready now!"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "Clean!"

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re bonus