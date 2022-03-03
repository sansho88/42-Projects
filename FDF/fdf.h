/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 18:08:29 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/18 11:40:47 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "minilibx_macos/mlx.h"
# include "get_next_line/get_next_line_bonus.h"
# include "libft/libft.h"
# include "colors.h"
# include "keys.h"
# include <math.h>
# include <fcntl.h>
# include <stdbool.h>
# define MAP_PATH "./test_maps/"
# define WIDTH 1300
# define HEIGHT 1200
# ifndef ZOOM
#  define ZOOM 10.0f
# endif
# ifndef OFFSET
#  define OFFSET 10.0f
# endif

/////////////////////////// STRUCTS ///////////////////////////////////////////
typedef struct s_data {
	void	*image;
	char	*address;
	int		bits_per_pixel;
	int		line_lentgh;
	int		endian;
}	t_data;

typedef struct s_map {
	int				xmax;
	int				ymax;
	int				**map;
	float			**mtx;
}	t_map;

typedef struct s_drawer{
	void			*mlx;
	void			*window;
	float			zoom;
	float			**offset;
	int				**projmtx;
	t_data			data;
	t_map			*map;
}	t_drawer;

typedef struct s_parsemap {
	char	*tmp;
	char	**mapsplit;
	int		**map;
	int		i;
	int		j;
}	t_parsemap;

/////////////////////////// FUNCTIONS /////////////////////////////////////////

// [lines.c]
void	bresenham(float *oldmtx, float *newmtx, t_drawer *drawer);
void	drawlineshorizontal(int **map, int xmax, int ymax, t_drawer *drawer);
void	drawlinesvertical(int **map, int xmax, int ymax, t_drawer *drawer);
void	putlines(t_map *map, t_drawer *drawer);
float	*iso(int x, int y, int z, float offset);

// [fdf_utils.c]
int		**parsemap(int fd, int xmax, int ymax);
void	getmapxymax(char *mapname, int *xmax, int *ymax);
void	optimized_pixelput(t_data *data, int x, int y, int color);
float	mod(float f);
float	max(float a, float b);

// [matrices.c]
int		**setprojectionmatrix(unsigned int zoom);
void	cleanmatrices(int **matrix, size_t	size);
float	*matrix_mul(int **projmatrix, float *coords);

// [keys.c]
int		key_hook(int keycode, t_drawer *drawer);

// [fdf.c]
bool	drawimage(t_drawer	*drawer);

#endif
