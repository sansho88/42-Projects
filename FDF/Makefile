# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/14 12:09:38 by tgriffit          #+#    #+#             #
#   Updated: 202#   Updated: 2022/02/18 10:39:42 by tgriffit         ###   ########.fr       #                              #
# ************************************************************************** #

NAME = fdf

FLAGS = -Wall -Werror -Wextra -g3 #-fsanitize=address
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
MLXLIB = -L ./minilibx_macos
DIR_SRCS = ./
DIR_OBJS = .objs

SRCS = lines.c matrices.c \
		fdf.c fdf_utils.c \
		keys.c \
		./get_next_line/get_next_line_bonus.c \

OBJS = $(SRCS:.c=.o)

all: libftmake mlxmake $(NAME)

$(NAME): $(OBJS)
	gcc  $(OBJS) $(FLAGS) $(MLXFLAGS) $(MLXLIB) -L libft -lft -o $(NAME)

%.o : %.c fdf.h Makefile
	gcc $(FLAGS) -c $< -o $@

#### LIBFT ####
libftmake:
	@make -C libft

libftclean:
	@make fclean -C ./libft/
##############

mlxmake:
	@make -C minilibx_macos
	cp minilibx_macos/libmlx.a .

mlxclean:
	make -C minilibx_macos clean
	rm libmlx.a

clean:
	rm $(OBJS)

fclean: libftclean clean mlxclean

re: fclean all

.PHONY: all clean fclean re libftmake libftclean mlxmake
