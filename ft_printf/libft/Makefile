# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/10 17:13:35 by tgriffit          #+#    #+#             #
#   Updated: 202#   Updated: 2021/12/15 17:02:55 by tgriffit         ###   ########.fr       #                                                              #
# ************************************************************************** #

NAME = libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
AR =  @ar rcs
RM = @rm -f

SRCS = ft_strlen.c \
		ft_putchar_ret.c \
		ft_putstr_ret.c \
		ft_putnbr_ret.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "Libft is ready now!"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "Libft is cleaned!"

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re