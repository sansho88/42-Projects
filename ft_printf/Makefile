# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:14:40 by tgriffit          #+#    #+#              #
#   Updated: 2021/12/15 18:41:01 by tgriffit         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror -O2
AR =  @ar rcs
RM = @rm -f

SRCS =	ft_printf.c \
		ft_putnbr_base_ret.c

OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libftprintf.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) libftmake
	cp libft/libft.a $(NAME)
	$(AR) $(NAME) $(OBJS)
	@echo "Libftprintf is ready now!"

libftmake:
	@cd libft/ && make all && cd ..

libftclean:
	@cd libft && make fclean && echo "Done!"

clean:
	$(RM) $(OBJS)
	@echo "The Libftprintf is cleaned now!"

fclean: clean libftclean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re libftmake libftclean