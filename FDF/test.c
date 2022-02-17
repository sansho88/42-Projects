/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 14:03:07 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/16 19:34:21 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
# include "fdf.h"


//const int zoom = 6;
int projection[2][3] = {
		{1 * ZOOM, 0, 1},
		{0, 1 * ZOOM, 1}
};

void	optimized_pixelput(t_data *data, int x, int y, int color)
{
	char *dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data -> address + (y * data->line_lentgh + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void print_square(t_drawer drawer, int x, int y, int z)
{
	for(int i = 0; i <= 1000; i++)
	{
		for (int j = 0; j <= 1000; j++)
		{
			if (((j == 10 || j == 1000) && i >= 10 )|| ((i == 10 || i == 1000) && j >= 10) )
				optimized_pixelput(&drawer.data, x + i/z, y + j/z, 0x01FF0000);
		}
	}
	mlx_put_image_to_window(drawer.mlx, drawer.window, drawer.data.image, x, y);
}

void print_circle(void *mlx, void *window, t_data img, int x, int y)
{
	for(int i = 0; i < 500; i++)
		for (int j = 0; j < 500; j++)
			optimized_pixelput(&img, i + j , i + j, 0x0100FF00);
	mlx_put_image_to_window(mlx, window, img.image, x, y);
}

int ft_splitlen(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

float mod(float f)
{
	if (f < 0)
		return (-f);
	return (f);
}

float *iso(int x, int y, int z)
{
	float *coords;

	coords = ft_calloc(sizeof(float *), 2);
	x = (x - z) / sqrt(2);
	y = (x + 2 * y + z ) / sqrt(6);
	coords[0] = (float)x;
	coords[1] = (float)y;
	return (coords);
}

void bresenham(float oldmtx[2], float const newmtx[2], t_drawer *drawer)
{
	float 	stepx;
	float 	stepy;
	float	max;

	stepx = newmtx[0] - oldmtx[0];
	stepy = newmtx[1] - oldmtx[1];

	max = MAX(mod(stepx), mod(stepy));
	stepx /= max;
	stepy /= max;
	while ((int)(oldmtx[0] - newmtx[0]) || (int)(oldmtx[1] - newmtx[1]))
	{
		optimized_pixelput(&drawer->data, (int)oldmtx[0], (int)oldmtx[1], RGB_WHITE);
		oldmtx[0] += stepx;
		oldmtx[1] += stepy;
	}
}

float *matrix_mul(int projmatrix[2][3], int *coords)
{
	int 	i;
	int 	j;
	float	*res;

	i = 0;
	res = ft_calloc(sizeof(float), 2);
	res[i] = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 3)
		{
			res[i] += (float)projmatrix[i][j] * (float)coords[j];
			j++;
		}
		i++;
	}
	free(coords);
	return (res);
}

int **parsemap(int fd, int xmax, int ymax)
{
	t_parsemap	pmap;

	pmap.i = 0;
	pmap.map = malloc(ymax * sizeof(int *));
	if (!pmap.map)
		return (NULL);
	pmap.tmp = get_next_line(fd);
	while (pmap.tmp)
	{
		pmap.j = -1;
		pmap.mapsplit = ft_split(pmap.tmp, ' ');
		pmap.map[pmap.i] = malloc(sizeof(int) * xmax);
		if (!pmap.map[pmap.i])
			return (NULL); // leaks de pmap.map + tout le contenu deja malloc avant et aussi pmap.tmp
		while (++pmap.j < xmax)
			pmap.map[pmap.i][pmap.j] = ft_atoi(pmap.mapsplit[pmap.j]);
		pmap.i++;
		free(pmap.tmp);
		pmap.tmp = get_next_line(fd);
	}
	free(pmap.tmp);
	return (pmap.map);
}

int	*createcoords(int x, int y, int z)
{
	int *res;

	res = calloc(sizeof(float), 3);
	res[0] = x;
	res[1] = y;
	res[2] = z;
	return (res);
}

void joinpoints(t_drawer *drawer, int x1, int x2, int y1, int y2)
{
	float	i;
	int		x;
	int		y;

	i = 0.0f;
	while (i <= 1)
	{
		x = x1 + (x2 - x1) * (int)i;
		y = y1 + (y2 - y1) * (int)i;
		i += 0.005f;
		optimized_pixelput(&drawer->data, x, y, RGB_WHITE);
	}
	mlx_put_image_to_window(drawer->mlx, drawer->window, drawer->data.image, 50, 50);
}

void zoompix(t_data *data, int x, int y)
{
	int i;
	int j;

	i = 0;
	while (i < ZOOM / 4)
	{
		j = 0;
		while (j < ZOOM / 4)
			optimized_pixelput(data, x + j++, y + i, RGB_WHITE);
		i++;
	}
}

void drawlineshorizontal(int **map, int xmax, int ymax, t_drawer *drawer)
{
	int		x;
	int		y;
	float	**matrices;
	float	mtxnull[2];

	matrices = ft_calloc(sizeof(float**), xmax * ymax);
	y = -1;
	while (matrices && ++y < ymax)
	{
		x = -1;
		while (++x < xmax)
		{
			matrices[x] = matrix_mul(projection, createcoords(x, y, map[y][x]));
			if (x > 0)
			{
				bresenham(matrices[x - 1], matrices[x], drawer);
				free(matrices[x - 1]);
			}
			else
				bresenham(mtxnull, matrices[x], drawer);
				/*bresenham((float *)oldmatrix, (float *)matrix, drawer); //[WORKS!!]
				 *oldmatrix = matrix;
				 * free(matrix); */
	   }
   }
	free(matrices);
}

void drawlinesvertical(int **map, int xmax, int ymax, t_drawer *drawer)
{
	int 	x;
	int 	y;
	float 	**allmatrices;

	allmatrices = ft_calloc(sizeof(float**), xmax * ymax);
	x = xmax ;
	while (x-- > 1)
	{
		y = ymax;
		while (y-- > 0)
		{
			//isovision = iso(x, y, map[y][x]);
			//puts("Oupsi");
			allmatrices[y] = matrix_mul(projection, createcoords(x, y, map[y][x]));
			if (y < ymax - 1)
				bresenham((float *)allmatrices[y + 1], (float *)allmatrices[y], drawer);
			/*matrix = matrix_mul(projection, createcoords(x, y - 1, map[y - 1][x]));
			bresenham((float *)oldmatrix, (float *)matrix, drawer);
			oldmatrix = matrix;*/
			//free(matrix);
		}
		//oldmatrix[1] = (float)(ymax - 1 ) * ZOOM; //TODO: The slice at the last line is there
	}
}

void putlines(int **map, t_drawer drawer, int xmax, int ymax)
{
	drawlineshorizontal(map, xmax, ymax, &drawer);
	drawlinesvertical(map, xmax, ymax, &drawer);

	//todo[DEBUG] Something wrong happens
	mlx_put_image_to_window(drawer.mlx, drawer.window, drawer.data.image, 50, 50);
}

void	getmapxymax(const char *pathmap, int *xmax, int *ymax)
{
	int fd;
	char	*s;

	fd = open(pathmap, O_RDONLY);
	*ymax = 0;
	s = get_next_line(fd);
	while (s)
	{
		(*ymax)++;
		*xmax = 0;
		int i = -1;
		while (s[++i])
		{
			if (ft_isdigit(s[i]) == 1 && (i == 0 || s[i - 1] == ' '
			|| s[i - 1] == '-'))
				(*xmax)++;
		}
		free(s);
		s = get_next_line(fd);
	}
	close (fd);
}

int	main(int argc, char **argv)
{
	char *testmap;
	if (argc > 1 && argc < 3)
		testmap = ft_strjoin(MAP_PATH, argv[1], 0);
	else
		testmap = ft_strjoin(MAP_PATH, "42.fdf", 0);
	puts(testmap);
	void	*mlx = mlx_init();
	void	*window = mlx_new_window(mlx, WIDTH, HEIGHT, testmap);
	t_drawer	drawer;
	t_data	img;
	
	img.image = mlx_new_image(mlx, WIDTH, HEIGHT);
	img.address = mlx_get_data_addr(img.image, &img.bits_per_pixel, &img.line_lentgh, &img.endian);
	printf("bits per pixel:%d, line_length: %d, endian:%d \n", img.bits_per_pixel, img.line_lentgh, img.endian);
	drawer.data = img;
	drawer.window = window;
	drawer.mlx = mlx;
	int xmax;
	int ymax;
	puts("\nCalculating the map size...");
	getmapxymax(testmap, &xmax, &ymax);
	int fd = open(testmap, O_RDONLY);
	puts("Parsing...");
	int **map = parsemap(fd, xmax, ymax);
	close(fd);
	int f = -1;
	while (++f < ymax)
	{
		dprintf(1, "\n");
		int a = -1;
		while (++a < xmax)
			dprintf(1, "%3d ", map[f][a]);
	}
	puts("\nLet's go les biches!");
	joinpoints(&drawer, 0, 0,0, 0 ); //It seems to inits Drawpoints...
	putlines(map, drawer, xmax, ymax); //TODO: TOFIX
	mlx_loop(mlx);

}