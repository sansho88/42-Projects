cmake_minimum_required(VERSION 3.20)
project(FDF C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

file(GLOB MLX_SRC CONFIGURE_DEPENDS "minilibx_macos/*.h" "minilibx_macos/*.c")

add_executable(FDF
         fdf.h /
        libft/libft.h libft/ft_atoi.c libft/ft_calloc.c libft/ft_bzero.c /
        libft/ft_strchr.c libft/ft_strdup.c libft/ft_isdigit.c libft/ft_split.c /
        libft/ft_strjoin.c libft/ft_memcpy.c libft/ft_strlen.c /
        get_next_line/get_next_line_bonus.c /
        ${MLX_SRC} colors.h matrices.c fdf_utils.c lines.c fdf.c keys.c keys.h keys_utils.c)
