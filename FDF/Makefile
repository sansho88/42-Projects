# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/14 12:09:38 by tgriffit          #+#    #+#             #
#   Updated: 2022/02/18 12:04:29 by tgriffit         ###   ########.fr       #                              #
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
	echo fdf is ready to use! Usage: ./fdf \<mapname.fdf\>
	echo "You can also zoom in and out with the + and - numpad keys.\nEnjoy!"
	echo "(Be sure that the map is correctly placed into the test_map folder.)"

%.o : %.c fdf.h Makefile
	gcc $(FLAGS) -c $< -o $@

#### LIBFT ####
libftmake:
	@make -C libft
	echo Libft ready!

libftclean:
	@make fclean -C ./libft/
	echo Libft cleaned.
##############

mlxmake:
	@make -C minilibx_macos
	cp minilibx_macos/libmlx.a .
	echo Minilibx ready!

mlxclean:
	make -C minilibx_macos clean
	rm libmlx.a
	echo Minilibx cleaned.

clean:
	rm $(OBJS)

fclean: libftclean clean mlxclean

re: fclean all

.PHONY: all clean fclean re libftmake libftclean mlxmake
.SILENT:
