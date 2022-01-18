# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/13 11:14:40 by tgriffit          #+#    #+#              #
#   Updated: 2022/01/11 16:39:23 by tgriffit         ###   ########.fr       # #
#                                                                              #
# **************************************************************************** #

NAME = libftminitalk
LIBFTPATH = ./libft/libft.a

CC = @gcc
CFLAGS = -Wall -Wextra -Werror -O2
AR =  @ar rcs
RM = @rm -f

SRCS =	binaryconverter.c \

OBJS = $(SRCS:.c=.o)

all: $(NAME) libftmake

%.o: %.c minitalk.h Makefile
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): libftmake client server
	@echo "Minitalk is ready to use now!"

#### LIBFT ####
libftmake:
	@make -C libft

libftclean:
	@make fclean -C ./libft/

################

#### EXECUTABLES ####
client: $(OBJS) client.o
	$(CC) $(CFLAGS) $(OBJS) client.o libft/libft.a  -o client
	@echo "You can use the \"./client [SERVER PID] [Message]\" command."

server: $(OBJS) server.o
	$(CC) $(CFLAGS) $(OBJS) server.o -L libft -lft -o server
	@echo "You can use the \"./server\" command."

bonus: all
	$(CC) $(CFLAGS) server_bonus.c libft/libft.a  $(SRCS) -o server_bonus
	$(CC) $(CFLAGS) client_bonus.c libft/libft.a  $(SRCS) -o client_bonus
	@echo "client_bonus and server_bonus are also ready to use."
#####################
clean:
	$(RM) $(OBJS) client.o server.o
	@echo "The Minitalk is cleaned now!"

fclean: clean libftclean
	$(RM) $(NAME) server client server_bonus client_bonus

re: clean all

.PHONY: all clean fclean re libftmake libftclean bonus
