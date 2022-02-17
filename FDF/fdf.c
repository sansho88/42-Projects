/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriffit <tgriffit@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 12:19:13 by tgriffit          #+#    #+#             */
/*   Updated: 2022/02/17 11:56:41 by tgriffit         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

#include <stdio.h>

/**
 * Prepare the window to be fully functionnal.
 * @param drawer : The structure which contains all the variables initialized
  				and then used by the mlx
 * @param map : The map.fdf which will be drawn.
 * @return false (=0) if mlx_get_data_addr failed.
 */


void	checkarg(int argc, char **argv, char **map)
{
	if (argc > 1 && argc < 3)
		*map = ft_strjoin(MAP_PATH, argv[1], 0);
	else
	{
		ft_putendl_fd("Correct usage: ./fdf <mapIntest_mapsFolder>.fdf", 2);
		exit(1);
	}
	if (open(*map, O_RDONLY) <= 0)
	{
		ft_putendl_fd("Error: map not found in test_map folder.", 2);
		exit(2);
	}
}


bool	drawimage(t_drawer	*drawer)
{
	drawer->data.image = mlx_new_image(drawer->mlx, WIDTH, HEIGHT);
	drawer->data.address = mlx_get_data_addr(drawer->data.image,
			&drawer->data.bits_per_pixel,
			&drawer->data.line_lentgh,
			&drawer->data.endian);
	if (!drawer->data.address)
		return (false);
	return (true);
}

int	main(int argc, char **argv)
{
	char		*testmap;
	t_drawer	drawer;
	int			fd;

	checkarg(argc, argv, &testmap);
	drawer.mlx = mlx_init();
	mlx_do_key_autorepeaton(drawer.mlx);
	ft_putendl_fd("\nCalculating the map size...", 1);
	drawer.map = malloc(sizeof(t_map));
	getmapxymax(testmap, &drawer.map->xmax, &drawer.map->ymax);
	drawer.window = mlx_new_window(drawer.mlx, WIDTH, HEIGHT, testmap);
	if (!drawimage(&drawer))
		return (1);
	ft_putendl_fd("Parsing...", 1);
	fd = open(testmap, O_RDONLY);
	drawer.map->map = parsemap(fd, drawer.map->xmax, drawer.map->ymax);
	close(fd);
	ft_putendl_fd("Let's go les biches!", 1);
	putlines(drawer.map, &drawer);
	free(testmap);
	mlx_key_hook(drawer.window, key_hook, &drawer);
	mlx_loop(drawer.mlx);
}
