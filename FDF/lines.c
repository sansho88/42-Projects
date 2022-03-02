/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lines.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:08:50 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/17 18:47:44 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	bresenham(float *oldmtx, float *newmtx, t_drawer *drawer)
{
	float	stepx;
	float	stepy;
	float	maxYX;

	stepx = newmtx[0] - oldmtx[0];
	stepy = newmtx[1] - oldmtx[1];
	maxYX = max(mod(stepx), mod(stepy));
	stepx /= maxYX;
	stepy /= maxYX;
	while ((int)(oldmtx[0] - newmtx[0]) || (int)(oldmtx[1] - newmtx[1]))
	{
		optimized_pixelput(&drawer->data, (int)oldmtx[0], (int)oldmtx[1],
			RGB_WHITE);
		oldmtx[0] += stepx;
		oldmtx[1] += stepy;
	}
}

void	drawlineshorizontal(int **map, int xmax, int ymax, t_drawer *drawer)
{
	int				x;
	int				y;
	float			**mtx;

	mtx = drawer->map->mtx;
	y = ymax;
	while (drawer->projmtx && mtx && y-- > 0)
	{
		x = xmax;
		while (x-- > 0)
		{
			free(mtx[x]);
			mtx[x] = matrix_mul(drawer->projmtx, iso(x, y, map[y][x], 42));
			if (x < xmax - 1)
				bresenham(mtx[x + 1], mtx[x], drawer);
		}
	}
	x = 0;
	while (x < xmax)
		free(mtx[x++]);
}

void	drawlinesvertical(int **map, int xmax, int ymax, t_drawer *drawer)
{
	int				x;
	int				y;
	float			**mtx;

	x = xmax ;
	mtx = drawer->map->mtx;
	while (drawer->projmtx && mtx && x-- > 0)
	{
		y = ymax;
		while (y-- > 0)
		{
			mtx[y] = matrix_mul(drawer->projmtx, iso(x, y, map[y][x], 42));
			if (y < ymax - 1)
			{
				bresenham(mtx[y + 1], mtx[y], drawer);
				free(mtx[y + 1]);
			}
		}
		free(mtx[0]);
	}
}

void	putlines(t_map *map, t_drawer *drawer)
{
	if (drawer->zoom <= 0)
		drawer->zoom = ZOOM;
	map->mtx = ft_calloc(sizeof(float *), map->xmax * map->ymax);
	drawer->projmtx = setprojectionmatrix(drawer->zoom);
	mlx_put_image_to_window(drawer->mlx, drawer->window, drawer->data.image, 0,
		0);
	drawlineshorizontal(map->map, map->xmax, map->ymax, drawer);
	drawlinesvertical(map->map, map->xmax, map->ymax, drawer);
	free(drawer->map->mtx);
	cleanmatrices(drawer->projmtx, 3);
	mlx_put_image_to_window(drawer->mlx, drawer->window, drawer->data.image,
		10, 10);
	mlx_destroy_image(drawer->mlx, drawer->data.image);
}

float	*iso(int x, int y, int z, float offset)
{
	float	*coords;
	float	prev_x;
	float	prev_y;
	float	new_x;
	float	new_y;

	prev_x = (float)x;
	prev_y = (float)y;
	new_x = (prev_x - prev_y) * (float)cos(0.523599) + offset;
	new_y = (float)-z + (prev_x + prev_y) * (float)sin(0.523599) + offset;
	coords = ft_calloc(sizeof(float *), 2);
	coords[0] = new_x;
	coords[1] = new_y;
	return (coords);
}
