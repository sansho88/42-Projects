# ************************************************************************** #
#                                                                            #
#                                                        :::      ::::::::   #
#   Makefile                                           :+:      :+:    :+:   #
#                                                    +:+ +:+         +:+     #
#   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        #
#                                                +#+#+#+#+#+   +#+           #
#   Created: 2022/01/14 12:09:38 by tgriffit          #+#    #+#             #
#   Updated: 202#   Updated: 2022/01/14 12:27:10 by tgriffit         ###   ########.fr       #                                                              #
# ************************************************************************** #

NAME = fdf.a

FLAGS = -Wall -Werror -Wextra
MLXFLAGS = -lmlx -framework OpenGL -framework AppKit
MLXLIB = -L ./minilibx_macos

SRCS = test.c \

OBJS = $(SRCS:.c =.o)

%.o : %.c
	gcc $(FLAGS) $(MLXFLAGS) $(MLXLIB) -c $< -o $@

all: $(NAME)
