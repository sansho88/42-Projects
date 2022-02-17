# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/14 12:09:38 by tgriffit          #+#    #+#             #
#   Updated: 2022/02/17 13:51:22 by tgriffit         ###   ########.fr       #                                              #
# ************************************************************************** #

NAME = fdf

FLAGS = -Wall -Werror -Wextra #-fsanitize=address -g3
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
MLXLIB = -L ./minilibx_macos
DIR_SRCS = ./
DIR_OBJS = .objs

SRCS = lines.c matrices.c \
		fdf.c fdf_utils.c \
		keys.c keys_utils.c \
		./get_next_line/get_next_line_bonus.c \

OBJS = $(SRCS:.c=.o)

%.o : %.c fdf.h Makefile
	gcc $(FLAGS) -c $< -o $@

all: $(NAME) libftmake

$(NAME): libftmake $(OBJS)
	gcc $(FLAGS) $(MLXFLAGS) $(MLXLIB) $(OBJS) -L libft -lft -o fdf

#### LIBFT ####
libftmake:
	@make -C libft

libftclean:
	@make fclean -C ./libft/
##############

clean:
	rm $(OBJS)

fclean: libftclean clean

re: clean all

.PHONY: all clean re libftmake libftclean
