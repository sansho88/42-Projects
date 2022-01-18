cmake_minimum_required(VERSION 3.20)
project(ft_printf C)

set(CMAKE_C_STANDARD 99)

add_executable(ft_printf ft_printf.h ft_printf.c ft_putnbr_base_ret.c libft/ft_putchar_ret.c libft/ft_putstr_ret.c libft/ft_putnbr_ret.c libft/ft_strlen.c main.c)
