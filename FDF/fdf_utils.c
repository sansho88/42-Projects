/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:05:26 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/18 11:37:15 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

/**
 * Copy the map.fdf into a double-array of integers
 * @param fd : The FileDescriptor of the map available for reading.
 * @param xmax
 * @param ymax
 * @return The map parsed formatted in map[y][x]
 */
int	**parsemap(int fd, int xmax, int ymax)
{
	t_parsemap	pmap;

	pmap.i = -1;
	pmap.map = malloc(ymax * sizeof(int *));
	if (!pmap.map)
		return (NULL);
	pmap.tmp = get_next_line(fd);
	while (pmap.tmp)
	{
		pmap.j = -1;
		pmap.mapsplit = ft_split(pmap.tmp, ' ');
		pmap.map[++pmap.i] = malloc(sizeof(int) * xmax);
		if (!pmap.map[pmap.i])
			return (NULL);
		while (++pmap.j < xmax)
		{
			pmap.map[pmap.i][pmap.j] = ft_atoi(pmap.mapsplit[pmap.j]);
			free(pmap.mapsplit[pmap.j]);
		}
		free(pmap.tmp);
		free(pmap.mapsplit);
		pmap.tmp = get_next_line(fd);
	}
	free(pmap.tmp);
	return (pmap.map);
}

/**
 * Used essentially for delimit the parsing at the init.
 * @param mapname
 * @param xmax :Address of the int which will receives the number of colomns
 * @param ymax :Address of the int which will receives the number of lines
 */
void	getmapxymax(char *mapname, int *xmax, int *ymax)
{
	int		fd;
	char	*s;
	int		i;

	fd = open(mapname, O_RDONLY);
	*ymax = 0;
	s = get_next_line(fd);
	while (s)
	{
		(*ymax)++;
		*xmax = 0;
		i = -1;
		while (s[++i])
		{
			if (ft_isdigit(s[i]) == 1 && (i == 0 || s[i - 1] == ' '
					|| s[i - 1] == '-'))
				(*xmax)++;
		}
		free(s);
		s = get_next_line(fd);
	}
	free(s);
	close (fd);
}

float	max(float a, float b)
{
	if (a > b)
		return (a);
	return (b);
}

float	mod(float f)
{
	if (f < 0)
		return (-f);
	return (f);
}

/**
 * Put the pixels into a stamp image, which will be applied by the
 * putpixeltowindow function.
 * @param data : Structure which contains the mlx pointers
 * @param x : Coordinate of the pixel
 * @param y : Coordinate of the pixel
 * @param color : See colors.h
 */
void	optimized_pixelput(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = data -> address + (y * data->line_lentgh + x
			* (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}
