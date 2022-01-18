# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    libft/Makefile                                     :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:14:40 by tgriffit          #+#    #+#              #
#   Updated: 2022/01/04 11:09:10 by tgriffit         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror
AR =  @ar rcs
RM = @rm -f

SRCS =  ft_atoi.c \
		ft_itoa.c \
		ft_strlen.c \
		ft_putchar.c \
		ft_putstr_fd.c \
		ft_putendl_fd.c \
		ft_strlcpy.c \
		ft_chrjoinfree.c \
		ft_memcpy.c


OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c libft.h
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "Libft is now compilated!"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "Libft is cleaned!"

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re