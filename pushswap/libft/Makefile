# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2021/11/10 17:13:35 by tgriffit          #+#    #+#             #
#   Updated: 2022/04/01 18:10:22 by tgriffit         ###   ########.fr       #
# ************************************************************************** #

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
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)
	@echo "Libft is ready now!"

clean:
	$(RM) $(OBJS) $(OBJS_BONUS)
	@echo "libft clean"

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re